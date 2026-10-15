

#include <stdio.h>
#include "sudoku.h"

// Stampa la griglia Sudoku in un formato leggibile.
void sudoku_print(const Sudoku *sudoku) {
    printf("+-------+-------+-------+\n");

    for (int row = 0; row < SUDOKU_SIZE; row++) {
        printf("| ");

        for (int col = 0; col < SUDOKU_SIZE; col++) {
            int value= sudoku -> cells[row][col];

            if (value == EMPTY_CELL) {
                printf(". ");
            } else {
                printf("%d ", value);
            }

            // Separa visivamente i box 3x3.
            if ((col + 1) % BOX_SIZE == 0) {
                printf("| ");
            }
        }

        printf("\n");

        // Inserisce una seperazione orizzontale ogni tre righe.
        if ((row + 1) % BOX_SIZE == 0) {
            printf("+-------+--------+--------+\n");
        }
    }
}

// Verifica che ogni riga non contenga duplicati.
static int sudoku_validate_rows(const Sudoku *sudoku) {
    for (int row = 0; row < SUDOKU_SIZE; row++) {
        int seen[SUDOKU_SIZE + 1] = {0};

        for (int col = 0; col < SUDOKU_SIZE; col++) {
            int value = sudoku->cells[row][col];

            // Le celle vuote non partecipano al controllo duplicati.
            if (value == EMPTY_CELL) {
                continue;
            }

            if (seen[value]) {
                printf("Invalid Sudoku: duplicate value %d in row %d.\n", value, row + 1);
                return 0;
            }

            seen[value] = 1;
        }
    }

    return 1;
}

// Verifica che ogni colonna non contenga duplicati.
static int sudoku_validate_columns(const Sudoku *sudoku) {
    for (int col = 0; col < SUDOKU_SIZE; col++) {
        int seen[SUDOKU_SIZE + 1] = {0};

        for (int row = 0; row < SUDOKU_SIZE; row++) {
            int value = sudoku->cells[row][col];

            // Le celle vuote non partecipano al controllo dei duplicati.
            if (value == EMPTY_CELL) {
                continue;
            }

            if (seen[value]) {
                printf("Invalid Sudoku: duplicate value %d in column %d.\n", value, col + 1);

                return 0;
            }

            seen[value] = 1;
        }
    }

    return 1;
}

// Verifica che ogni box 3x3 non contenga duplicati.
static int sudoku_validate_boxes(const Sudoku *sudoku) {
    for (int box_row = 0; box_row < SUDOKU_SIZE; box_row += BOX_SIZE) {
        for (int box_col = 0; box_col < SUDOKU_SIZE; box_col += BOX_SIZE) {
            int seen[SUDOKU_SIZE + 1] = {0};

            // Scorre le 9 celle del box corrente.
            for (int row = box_row; row < box_row + BOX_SIZE; row++) {
                for (int col = box_col; col < box_col + BOX_SIZE; col++) {
                    int value = sudoku->cells[row][col];

                    // Le celle vuote non partecipano al controllo.
                    if (value == EMPTY_CELL) {
                        continue;
                    }

                    if (seen[value]) {
                        int box_number = (box_row / BOX_SIZE) * BOX_SIZE + (box_col / BOX_SIZE) + 1;
                        
                        printf("Invalid Sudoku: duplicate value %d in box %d.\n", value, box_number);

                        return 0;
                    }

                    seen[value] = 1;
                }
            }
        }
    }

    return 1;
}

// Verifica che la griglia rispetti le regole del Sudoku.
int sudoku_validate(const Sudoku *sudoku) {
    if (!sudoku_validate_rows(sudoku)) {
        return 0;
    }

   if(!sudoku_validate_columns(sudoku)){
    return 0;
   }

   if(!sudoku_validate_boxes(sudoku)) {
    return 0;
   }

   return 1;
}

// Verifica se tutte le celle della griglia sono state compilate.
int sudoku_is_complete(const Sudoku *sudoku) {
    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            if (sudoku -> cells[row][col] == EMPTY_CELL) {
                return 0;
            }
        }
    }

    return 1;
}