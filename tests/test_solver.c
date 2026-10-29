

#include <assert.h>
#include <stdio.h>

#include "solver.h"

int main(void) {
    // Griglia di prova per verificare solver.
    Sudoku puzzle = {
        .cells = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    // Il valore 5 e' gia' presente nella prima riga.
    assert(solver_can_place(&puzzle, 0, 2, 5) == 0);

    // Il valore 4 e' gia' presente nella quarta colonna.
    assert(solver_can_place(&puzzle, 0, 3, 4) == 0);

    // Il valore 9 e' gia' presente nel box 3x3 superiore sinistro.
    assert(solver_can_place(&puzzle, 0, 2, 9) == 0);

    // Il valore 4 puo' essere inserito nella cella [0][2].
    assert(solver_can_place(&puzzle, 0, 2, 4) == 1);

    // Valori esterni all'intervallo 1-9 non sono validi.
    assert(solver_can_place(&puzzle, 0, 2, 0) == 0);
    assert(solver_can_place(&puzzle, 0, 2, 10) == 0);

    Sudoku puzzle_to_solve = {
        .cells = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    // Il solver deve trovare una soluzione.
    assert(solver_solve(&puzzle_to_solve) == 1);

    // Controlla alcune celle della soluzione attesa.
    assert(puzzle_to_solve.cells[0][2] == 4);
    assert(puzzle_to_solve.cells[0][3] == 6);
    assert(puzzle_to_solve.cells[8][0] == 3);
    assert(puzzle_to_solve.cells[8][8] == 9);

    Sudoku unsolvable_puzzle = {
        .cells = {
            {1, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    // La griglia rispetta i vincoli iniziali, ma non possiede una soluzione.
    assert(solver_solve(&unsolvable_puzzle) == 0);

    // Dopo il fallimento, il backtracking deve aver annullato
    // tutte le modifiche effettuate sulle celle vuote.
    assert(unsolvable_puzzle.cells[0][2] == EMPTY_CELL);

    Sudoku stats_puzzle = {
        .cells = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    SolverStats stats = {0};

    // Il solver deve risolvere la griglia e raccogliere statistiche.
    assert(solver_solve_with_stats(&stats_puzzle, &stats) == 1);

    // Devono essere state effettuate delle assegnazioni.
    assert(stats.assignments > 0);

    // I backtrack non possono superare il numero di assegnazioni.
    assert(stats.backtracks <= stats.assignments);

    printf(
        "Backtracking stats - Assignments: %lu, Backtracks: %lu\n",
        stats.assignments,
        stats.backtracks
    );

    Sudoku mrv_stats_puzzle = {
        .cells = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    SolverStats mrv_stats = {0};

    // Il solver MRV deve risolvere la stessa griglia.
    assert(solver_solve_mrv_with_stats(
        &mrv_stats_puzzle,
        &mrv_stats
    ) == 1);

    // Devono essere state effettuate delle assegnazioni.
    assert(mrv_stats.assignments > 0);

    // I backtrack non possono superare le assegnazioni.
    assert(mrv_stats.backtracks <= mrv_stats.assignments);

    printf(
        "MRV stats          - Assignments: %lu, Backtracks: %lu\n",
        mrv_stats.assignments,
        mrv_stats.backtracks
    );

    assert(mrv_stats.assignments <= stats.assignments);
    assert(mrv_stats.backtracks <= stats.backtracks);

    Sudoku uniqueness_unique = {
        .cells = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    assert(
        solver_check_uniqueness(&uniqueness_unique)
        == SOLVER_UNIQUE_SOLUTION
    );

    Sudoku uniqueness_unsolvable = {
        .cells = {
            {1, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    assert(
        solver_check_uniqueness(&uniqueness_unsolvable)
        == SOLVER_NO_SOLUTION
    );

    Sudoku uniqueness_multiple = {
        .cells = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
        }
    };

    assert(
        solver_check_uniqueness(&uniqueness_multiple)
        == SOLVER_MULTIPLE_SOLUTIONS
    );

    printf("All solver tests passed.\n");
    
    return 0;
}