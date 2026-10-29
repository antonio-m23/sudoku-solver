

#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"

// Contiene le statistiche raccolte durante la risoluzione.
typedef struct {
    unsigned long assignments;
    unsigned long backtracks;
} SolverStats;

// Rappresenta il numero di soluzioni individuate per un Sudoku.
typedef enum {
    SOLVER_NO_SOLUTION = 0,
    SOLVER_UNIQUE_SOLUTION = 1,
    SOLVER_MULTIPLE_SOLUTIONS = 2
} SolverSolutionStatus;

// Verifica che un valore può essere inserito in una determinata cella, senza violare le regole.
int solver_can_place (
    const Sudoku *sudoku,
    int row,
    int col,
    int value
);

// Risolve la griglia Sudoku utilizzando il backtracking.
int solver_solve(Sudoku *sudoku);

// Risolve la griglia Sudoku e raccoglie statistiche sull'esecuzione.
int solver_solve_with_stats(
    Sudoku *sudoku,
    SolverStats *stats
);

// Risolve la griglia Sudoku utilizzando backtracking e MRV.
int solver_solve_mrv(Sudoku *sudoku);

// Risolve la griglia utilizzando MRV e raccoglie statistiche.
int solver_solve_mrv_with_stats(
    Sudoku *sudoku,
    SolverStats *stats
);

// Determina se il Sudoku non ha soluzioni, ne ha una sola
// oppure possiede soluzioni multiple.
SolverSolutionStatus solver_check_uniqueness(
    const Sudoku *sudoku
);

#endif