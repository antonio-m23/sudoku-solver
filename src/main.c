

#include <stdio.h>
#include <stdlib.h>
#include <sudoku.h>
#include <input.h>

int main (void) {
    int choice;

    // Mostra il menu iniziale.
    printf("========================\n");
    printf("      SUDOKU SOLVER\n");
    printf("========================\n\n");

    printf("1. Insert Sudoku manually\n");
    printf("2. Load Sudoku from file\n");
    printf("3. Exit\n");

    // Delega al modulo input la lettura/validazione della scelta.
    choice = input_read_menu_choice();

    // Gestisce scelta utente.
    switch (choice) {
        case 1:
            Sudoku puzzle = {0}; // Inizializza la griglia a zero.

            if (input_read_manual_sudoku(&puzzle)) {
                printf("Sudoku entered successfully.\n");
            }
            break;
        case 2:
            printf("File input selected.\n");
            break;
        case 3:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid option. Please enter 1, 2 or 3.\n");
            break;
    }
   

    return 0;
}