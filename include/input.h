

#ifndef INPUT_H
#define INPUT_H

#include "sudoku.h"

// Legge e valida la scelta dell'utente dal menu principale.
int input_read_menu_choice(void);

// Legge manualmente una griglia sudoku riga x riga.
int input_read_manual_sudoku(Sudoku *sudoku);

#endif