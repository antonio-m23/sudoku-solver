

#include <stdio.h>
#include <time.h>

#include "solver.h"

#define BENCHMARK_RUNS 1000

int main(void) {
    const Sudoku benchmark_puzzle = {
        .cells = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        }
    };

    Sudoku basic_stats_puzzle = benchmark_puzzle;
    Sudoku mrv_stats_puzzle = benchmark_puzzle;

    SolverStats basic_stats = {0};
    SolverStats mrv_stats = {0};

    solver_solve_with_stats(
        &basic_stats_puzzle,
        &basic_stats
    );

    solver_solve_mrv_with_stats(
        &mrv_stats_puzzle,
        &mrv_stats
    );

        clock_t basic_start = clock();

    for (int i = 0; i < BENCHMARK_RUNS; i++) {
        Sudoku puzzle = benchmark_puzzle;

        solver_solve(&puzzle);
    }

    clock_t basic_end = clock();

    double basic_total_ms =
        ((double)(basic_end - basic_start) / CLOCKS_PER_SEC) * 1000.0;

    double basic_average_ms =
        basic_total_ms / BENCHMARK_RUNS;

            clock_t mrv_start = clock();

    for (int i = 0; i < BENCHMARK_RUNS; i++) {
        Sudoku puzzle = benchmark_puzzle;

        solver_solve_mrv(&puzzle);
    }

    clock_t mrv_end = clock();

    double mrv_total_ms =
        ((double)(mrv_end - mrv_start) / CLOCKS_PER_SEC) * 1000.0;

    double mrv_average_ms =
        mrv_total_ms / BENCHMARK_RUNS;

    printf("Sudoku Solver Benchmark\n");
    printf("-----------------------\n");
    printf("Runs per algorithm: %d\n\n", BENCHMARK_RUNS);

    printf("Basic Backtracking\n");
    printf("Assignments: %lu\n", basic_stats.assignments);
    printf("Backtracks:  %lu\n", basic_stats.backtracks);
    printf("Average time: %.6f ms\n\n", basic_average_ms);

    printf("MRV Backtracking\n");
    printf("Assignments: %lu\n", mrv_stats.assignments);
    printf("Backtracks:  %lu\n", mrv_stats.backtracks);
    printf("Average time: %.6f ms\n", mrv_average_ms);

    return 0;
}