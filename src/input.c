

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


// Legge griglia sudoku da file testo.
int input_read_sudoku_file(const char *filename, Sudoku *sudoku) {
    FILE *file;
    char row_input[SUDOKU_SIZE + 3];

    // Apre il file in modalità lettura.
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: unable to open file '%s'.\n", filename);
        return 0;
    }

    // Legge esattamente le 9 righe della griglia.
    for (int row = 0; row < SUDOKU_SIZE; row++) {
        if (fgets(row_input, sizeof(row_input), file) == NULL) {
            printf("Invalid file: expected %d rows.\n", SUDOKU_SIZE);
            fclose(file);
            return 0;
        }

        size_t length = strlen(row_input);

        // Rimuove il newline finale, se presente.
        if (length > 0 && row_input[length - 1] == '\n') {
            row_input[length - 1] = '\0';
            length--;
        }

        // Ogni riga deve contenere esattamente SUDOKU_SIZE caratteri.
        if (length != SUDOKU_SIZE) {
            printf("Invalid file: row %d must contain exactly %d characters.\n", row + 1, SUDOKU_SIZE);

            fclose(file);
            return 0;
        }

        // Controlla e converte ogni cella.
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            char cell = row_input[col];

            if (cell >= '1' && cell <= '9') {
                sudoku->cells[row][col] = cell - '0';
            } else if (cell == '.' || cell == '-') {
                sudoku->cells[row][col] = EMPTY_CELL;
            } else {
                printf("Invalid file: invalid character '%c' at row %d , column %d.\n", cell, row +1, col +1);

                fclose(file);
                return 0;
            }
        }
    }

    // Dopo la nona riga non devono esserci altre righe.
    if (fgets(row_input, sizeof(row_input), file) != NULL) {
        printf("Invalid file: too many rows.\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}