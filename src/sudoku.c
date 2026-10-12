

#include <stdio.h>
#include "sudoku.h"

// Stampa alcuni valori per verificare il modello dei dati.
void sudoku_print_test(const Sudoku *sudoku) {
    printf("Sudoku Puzzle:\n");
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            printf("%d ", sudoku->cells[i][j]);
        }
        printf("\n");
    }
}