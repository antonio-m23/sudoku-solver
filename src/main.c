

#include <stdio.h>
#include <sudoku.h>

int main (void) {
    // Crea una variabile di tipo sudoku.
    Sudoku puzzle = {0};

    // Inserisce alcuni valori di esempio nella griglia.
    puzzle.cells[0][0] = 5;
    puzzle.cells[0][1] = 3;
    puzzle.cells[1][0] = 7;

    // Delega al modulo Sudoku la stampa dei valori per verificare il modello dei dati.
    sudoku_print_test(&puzzle);
   

    return 0;
}