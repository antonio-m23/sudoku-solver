

#include <stddef.h>

#include "solver.h"

// Cerca la prima cella vuota nella griglia.
// Restituisce 1 se la trova e salva le coordinate in row e col.
// Restituisce 0 se la griglia non contiene celle vuote.
static int solver_find_empty(
    const Sudoku *sudoku,
    int *row,
    int *col
) {
    for (int r = 0; r < SUDOKU_SIZE; r++) {
        for (int c = 0; c < SUDOKU_SIZE; c++) {
            if (sudoku->cells[r][c] == EMPTY_CELL) {
                *row = r;
                *col = c;
                return 1;
            }
        }
    }

    return 0;
}

// Verifica che un valore può essere inserito in una determinata cella, senza violare le regole.
int solver_can_place (
    const Sudoku *sudoku,
    int row,
    int col,
    int value
) {
    // Controlla che il valore appartenga all'intervallo valido (1-9).
    if (value < 1 || value > SUDOKU_SIZE) {
        return 0;
    }

    // Controlla la riga e la colonna della cella.
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        if (sudoku -> cells[row][i] == value) {
            return 0;
        }

        if (sudoku -> cells[i][col] == value) {
            return 0;
        }
    }

    // Calcola la posizione iniziale del box 3x3 contenente la cella.
    int box_start_row = (row / BOX_SIZE) * BOX_SIZE;
    int box_start_col = (col /BOX_SIZE) * BOX_SIZE;

    // Controlla tutte le celle del box 3x3.
    for (int r = box_start_row; r < box_start_row + BOX_SIZE; r++) {
        for (int c = box_start_col; c < box_start_col + BOX_SIZE; c++) {
            if (sudoku -> cells[r][c] == value) {
                return 0;
            }
        }
    }

    return 1;
}

// Conta quanti valori validi possono essere inseriti in una cella vuota.
static int solver_count_candidates(
    const Sudoku *sudoku,
    int row,
    int col
) {
    int count = 0;

    for (int value = 1; value <= SUDOKU_SIZE; value++) {
        if (solver_can_place(sudoku, row, col, value)) {
            count++;
        }
    }

    return count;
}

// Trova la cella vuota con il minor numero di candidati validi.
static int solver_find_mrv_cell(
    const Sudoku *sudoku,
    int *row,
    int *col
) {
    int min_candidates = SUDOKU_SIZE + 1;
    int found = 0;

    for (int r = 0; r < SUDOKU_SIZE; r++) {
        for (int c = 0; c < SUDOKU_SIZE; c++) {
            if (sudoku -> cells[r][c] != EMPTY_CELL) {
                continue;
            }

            int candidates = solver_count_candidates(sudoku, r, c);

            if (candidates < min_candidates) {
                min_candidates = candidates;
                *row = r;
                *col = c;
                found = 1;
            }

            // Nessun candidato significa che il ramo corrente non può portare ad una soluzione.
            if (min_candidates == 0) {
                return 1;
            }
        }
    }

    return found;
}

// Implementa il backtracking ricorsivo e, se richiesto, aggiorna statistiche durante la ricerca.
static int solver_solve_recursive(
    Sudoku *sudoku,
    SolverStats *stats
) {
    int row;
    int col;

    // Se non esistono più celle vuote, il Sudoku è risolto.
    if (!solver_find_empty(sudoku, &row, &col)) {
        return 1;
    }

    // Prova tutti i valori possibili da 1 a 9.
    for (int value = 1; value <= SUDOKU_SIZE; value++) {
        if (solver_can_place(sudoku, row, col, value)) {
            // Inserisce temporaneamente un candidato valido.
            sudoku -> cells[row][col] = value;

            if (stats != NULL) {
                stats -> assignments++;
            }

            // Prosegue ricorsivamente dalla nuova configurazione.
            if (solver_solve_recursive(sudoku, stats)) {
                return 1;
            }

            // La scelta non porta ad una soluzione: annulla la mossa.
            sudoku -> cells[row][col] = EMPTY_CELL;

            if (stats != NULL) {
                stats -> backtracks++;
            }
        }
    }

    return 0;
}

// Implementa il backtracking utilizzando l'euristica MRV.
static int solver_solve_mrv_recursive(
    Sudoku *sudoku,
    SolverStats *stats
) {
    int row;
    int col;

    // Se non esistono celle vuote, il Sudoku è risolto.
    if (!solver_find_mrv_cell(sudoku, &row, &col)) {
        return 1;
    }

    // Prova tutti i valori possibili nella cella scelta da MRV.
    for (int value = 1; value <= SUDOKU_SIZE; value++) {
        if (solver_can_place(sudoku, row, col, value)) {
            sudoku -> cells[row][col] = value;

            if (stats != NULL) {
                stats -> assignments++;
            }

            if (solver_solve_mrv_recursive(sudoku, stats)) {
                return 1;
            }

            sudoku -> cells[row][col] = EMPTY_CELL;

            if (stats != NULL) {
                stats -> backtracks++;
            }
        }
    }

    return 0;
}

// Conta le soluzioni del Sudoku fino ad un massimo di due.
static void solver_count_solutions_recursive(
    Sudoku *sudoku,
    int *solution_count
){
    int row;
    int col;

    // Se abbiamo già trovato due soluzioni, possiamo fermarci.
    if (*solution_count >= 2) {
        return;
    }

    // Se non esistono celle vuote, abbiamo una soluzione completa.
    if (!solver_find_mrv_cell(sudoku, &row, &col)) {
        (*solution_count)++;
        return;
    }

    for (int value = 1; value <= SUDOKU_SIZE; value++) {
        if (solver_can_place(sudoku, row, col, value)) {
            sudoku -> cells[row][col] = value;

            solver_count_solutions_recursive(
                sudoku,
                solution_count
            );

            // Ripristina sempre la cella per continuare la ricerca.
            sudoku -> cells[row][col] = EMPTY_CELL;

            // Non serve esplorare altri rami dopo la seconda soluzione.
            if (*solution_count >= 2) {
                return;
            }
        }
    }
}

// Risolve la griglia sudoku senza raccogliere statistiche.
int solver_solve(Sudoku *sudoku) {
    return solver_solve_recursive(sudoku, NULL);
}

// Risolve la griglia Sudoku raccogliendo statistiche sull'esecuzione.
int solver_solve_with_stats(
    Sudoku *sudoku,
    SolverStats *stats
) {
    if (stats == NULL) {
        return solver_solve(sudoku);
    }

    // Azzera i contatori prima di ogni nuova risoluzione.
    stats -> assignments = 0;
    stats -> backtracks = 0;

    return solver_solve_recursive(sudoku, stats);
}

int solver_solve_mrv(Sudoku *sudoku) {
    return solver_solve_mrv_recursive(sudoku, NULL);
}

int solver_solve_mrv_with_stats(
    Sudoku *sudoku,
    SolverStats *stats
) {
    if (stats == NULL) {
        return solver_solve_mrv(sudoku);
    }

    stats -> assignments = 0;
    stats -> backtracks = 0;
    
    return solver_solve_mrv_recursive(sudoku, stats);
}

SolverSolutionStatus solver_check_uniqueness(
    const Sudoku *sudoku
) {
    Sudoku puzzle_copy = *sudoku;
    int solution_count = 0;

    solver_count_solutions_recursive(
        &puzzle_copy,
        &solution_count
    );

    if (solution_count == 0) {
        return SOLVER_NO_SOLUTION;
    }

    if (solution_count == 1) {
        return SOLVER_UNIQUE_SOLUTION;
    }

    return SOLVER_MULTIPLE_SOLUTIONS;
}