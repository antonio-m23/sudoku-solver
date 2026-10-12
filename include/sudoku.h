

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

// Stampa alcuni valori per verificare il modello dei dati.
void sudoku_print_test(const Sudoku *Sudoku);

#endif