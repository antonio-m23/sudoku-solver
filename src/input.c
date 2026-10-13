

#include <stdio.h>
#include <stdlib.h>
#include "input.h"

// Legge una scelta valida per il menu principale.
int input_read_menu_choice(void) {
    char input[32];
    char *endptr;
    long choice;

    while (1) {
        printf("Select an option:  ");

        // Legge l'intera riga inserita da utente.
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error. Please try again.\n");
            continue;
        }

        // Converte l'input testuale in intero.
        choice =strtol(input, &endptr, 10);

        // Nessuna cifra valida trovata.
        if (endptr == input) {
            printf("Invalid option. Please enter 1, 2 or 3.\n\n");
            continue;
        }

        // Dopo il numero sono presenti caratteri non validi.
        if (*endptr != '\n' && *endptr != '\0') {
            printf("Invalid option. Please enter 1, 2 or 3.\n\n");
            continue;
        }

        // Controlla se la scelta è tra 1 e 3.
        if (choice < 1 || choice > 3) {
            printf("Invalid option. Please enter 1, 2 or 3.\n\n");
            continue;
        }

        return (int)choice;
    }
}


int input_read_manual_sudoku (Sudoku *sudoku) {
    char row_input[SUDOKU_SIZE + 2]; // +2 per '\n' e '\0'

    for (int row = 0; row < SUDOKU_SIZE; row++) {
        while (1) {
            printf("Enter row %d  ", row + 1);

            // Legge una riga completa da input.
            if (fgets(row_input, sizeof(row_input), stdin) == NULL) {
                printf("Input error. Please try again.\n");
                continue;
            }

            // Ogni riga deve contenere esattamente SUDOKU_SIZE caratteri più il terminatore di riga.
            if (row_input[SUDOKU_SIZE] != '\n') {
                printf("Invalid row. Please enter exactly %d digits (0-9) for row %d.\n", SUDOKU_SIZE, row + 1);

                // Pulisce il buffer input.
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {

                }

                continue;
        }

        int valid = 1;

        // Controlla e converte caratteri riga.
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            char cell = row_input[col];

            if (cell >= '1' && cell <= '9') {
                sudoku->cells[row][col] = cell = '0';
            } else if (cell == '.' || cell == '-') {
                sudoku->cells[row][col] = EMPTY_CELL;
            } else {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Invalid row. Use only digits 1-9, '.' or '-',\n");
            continue;
        }

        break;
    }
}

return 1;
}