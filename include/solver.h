

#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"

// Verifica che un valore può essere inserito in una determinata cella, senza violare le regole.
int solver_can_place (
    const Sudoku *sudoku,
    int row,
    int col,
    int value
);

// Risolve la griglia Sudoku utilizzando il backtracking.
// Restituisce 1 se trova una soluzione, 0 altrimenti.
int solver_solve(Sudoku *sudoku);

#endif