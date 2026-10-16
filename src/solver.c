

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

// Risolve la griglia Sudoku utilizzando il backtracking.
int solver_solve(Sudoku *sudoku) {
    int row;
    int col;

    // Se non esistono piu' celle vuote, il Sudoku e' risolto.
    if (!solver_find_empty(sudoku, &row, &col)) {
        return 1;
    }

    // Prova tutti i valori possibili da 1 a 9.
    for (int value = 1; value <= SUDOKU_SIZE; value++) {
        if (solver_can_place(sudoku, row, col, value)) {
            // Inserisce temporaneamente il valore nella cella.
            sudoku->cells[row][col] = value;

            // Prosegue ricorsivamente dalla nuova configurazione.
            if (solver_solve(sudoku)) {
                return 1;
            }

            // La scelta non porta a una soluzione: annulla la mossa.
            sudoku->cells[row][col] = EMPTY_CELL;
        }
    }

    // Nessun valore permette di risolvere questa configurazione.
    return 0;
}