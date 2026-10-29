

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#include "input.h"
#include "solver.h"


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
        case 1: {
            Sudoku puzzle = {0}; // Inizializza la griglia a zero.

            if (input_read_manual_sudoku(&puzzle)) {
                printf("Sudoku entered successfully.\n");
            }

            sudoku_print(&puzzle);
            
            if (sudoku_validate(&puzzle)) {
                if (sudoku_is_complete(&puzzle)) {
                    printf("\nThe sudoku is already complete and valid.\n");
                } else {
                    printf("\nSudoku is valid. Analyzing...\n\n");

                    SolverSolutionStatus status = solver_check_uniqueness(&puzzle);

                    if (status == SOLVER_NO_SOLUTION) {
                        printf("No solution exists for this Sudoku.\n");
                    } else if (status == SOLVER_UNIQUE_SOLUTION) {
                        solver_solve_mrv(&puzzle);

                        printf("Unique solution found:\n\n");
                        sudoku_print(&puzzle);
                    } else {
                        solver_solve_mrv(&puzzle);

                        printf("Multiple solutions exist.\n");
                        printf("One possible solution is: \n\n");
                        sudoku_print(&puzzle);
                    }
                }
            }

            break;
        }
        case 2: {
            Sudoku puzzle = {0};
            char filename[256];

            // Richiede all'utente il percorso del file da caricare.
            printf("Enter a file path: ");

            if (fgets(filename, sizeof(filename), stdin) == NULL) {
                printf("Input error.\n");
                break;
            }

            // Rimuove eventuali caratteri di fine riga aggiunti da fgets.
            filename[strcspn(filename, "\r\n")] = '\0';

            // Tenta di caricare il Sudoku dal file specificato.
            if (input_read_sudoku_file(filename, &puzzle)) {
                printf("Sudoku loaded successfully.\n");
            }

            sudoku_print(&puzzle);

            if (sudoku_validate(&puzzle)) {
                if (sudoku_is_complete(&puzzle)) {
                    printf("\nThe sudoku is already complete and valid.\n");
                } else {
                    printf("\nSudoku is valid. Analyzing...\n\n");

                    SolverSolutionStatus status = solver_check_uniqueness(&puzzle);

                    if (status == SOLVER_NO_SOLUTION) {
                        printf("No solution exists for this Sudoku.\n");
                    } else if (status == SOLVER_UNIQUE_SOLUTION) {
                        solver_solve_mrv(&puzzle);

                        printf("Unique solutiuon found.\n\n");
                        sudoku_print(&puzzle);
                    } else {
                        solver_solve_mrv(&puzzle);

                        printf("Multiple solutions exist. \n");
                        printf("One possible solution is: \n\n");
                        sudoku_print(&puzzle);
                    }
                }
            }

            break;
        }
        case 3:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid option. Please enter 1, 2 or 3.\n");
            break;
    }
   

    return 0;
}