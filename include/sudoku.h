

#ifndef SUDOKU_H
#define SUDOKU_H

// Dimensione Standard della griglia Sudoku
#define SUDOKU_SIZE 9
#define BOX_SIZE 3

// Valore interno per rappresentare una cella vuota
#define EMPTY_CELL 0

typedef struct {
    int cells[SUDOKU_SIZE][SUDOKU_SIZE];
} Sudoku;

// Stampa la griglia Sudoku in un formato leggibile.
void sudoku_print(const Sudoku *sudoku);

// Verifica che la griglia rispetti le regole del Sudoku.
int sudoku_validate(const Sudoku *sudoku);

// Verifica se tutte le celle della griglia sono state compilate.
int sudoku_is_complete(const Sudoku *sudoku);

#endif