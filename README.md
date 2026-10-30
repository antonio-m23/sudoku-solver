# 🧩 Sudoku Solver

A command-line Sudoku solver written in C, built to explore backtracking algorithms, heuristic optimization, modular program design, and performance analysis.

The solver supports both manual input and text-file loading, validates Sudoku grids, detects unsolvable or non-unique puzzles, and solves valid puzzles using an optimized backtracking algorithm with the **Minimum Remaining Values (MRV)** heuristic.

The project also includes automated tests and a dedicated benchmark comparing basic backtracking with the MRV-optimized solver.


## ✨ Features

- Manual input and `.txt` file loading
- Sudoku validation for rows, columns, and 3×3 boxes
- Detection of completed, unsolvable, unique, and multiple-solution puzzles
- Recursive backtracking solver with MRV optimization
- Solver statistics for assignments and backtracks
- Automated tests and performance benchmarking


## 🧠 How It Works

The program follows a simple pipeline:

1. Read the Sudoku from manual input or a `.txt` file
2. Validate rows, columns, and 3×3 boxes
3. Check whether the puzzle is already complete
4. Analyze the number of possible solutions
5. Solve the puzzle using backtracking with the MRV heuristic
6. Display the result in a formatted grid

The project is split into separate modules for input handling, Sudoku logic, and solving, keeping the code easier to maintain and extend.


## ⚡ MRV Optimization

The basic backtracking solver selects the first empty cell it finds and tries every valid value.

The optimized solver instead uses the **Minimum Remaining Values (MRV)** heuristic, selecting the empty cell with the fewest valid candidates first.

This reduces unnecessary search branches and can significantly decrease the number of assignments and backtracks required to solve a puzzle.


## 📊 Performance

The project includes a reference benchmark that compares the basic backtracking solver with the MRV-optimized version using the same Sudoku puzzle.

**Basic Backtracking**
- 4,208 assignments
- 4,157 backtracks

**Backtracking + MRV**
- 51 assignments
- 0 backtracks

For this benchmark puzzle, MRV reduces the number of assignments by approximately **98.8%** and completely eliminates backtracking.

These results are specific to the reference test case and are intended to show the impact of the heuristic rather than represent the performance of every possible Sudoku.


## 📁 Project Structure

```text
sudoku-solver/
├── examples/   # Example Sudoku files
├── include/    # Header files
├── src/        # Application source code
├── tests/      # Automated tests and performance benchmark
├── .gitignore
├── LICENSE
└── README.md
```

The project is organized into separate directories for source code, headers, tests, benchmarks, and example puzzles, keeping the codebase clean and easy to navigate.


## 🚀 Getting Started

Clone the repository:

```bash
git clone https://github.com/antonio-m23/sudoku-solver.git
cd sudoku-solver
```

Compile the application with GCC:

```bash
gcc -Wall -Wextra -Wpedantic src/main.c src/sudoku.c src/input.c src/solver.c -Iinclude -o sudoku
```

Run the program:

```bash
./sudoku
```

On Windows, the compiled executable can also be launched as:

```bash
./sudoku.exe
```


## 🎮 Usage

When the program starts, choose one of the available options:

```text
1. Insert Sudoku manually
2. Load Sudoku from file
3. Exit
```

If you choose manual input, the program asks for the Sudoku **one row at a time**. Each row must contain exactly 9 characters.

Empty cells can be represented with either `.` or `-`.

Example:

```text
53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79
```

If you choose to load a Sudoku from a file, the program asks for the **file name or path** and reads the puzzle from the specified `.txt` file.

The file must use the same 9-row format shown above.


## 🧪 Testing

The project includes automated tests for the solver logic, including valid placements, solvable and unsolvable puzzles, MRV behavior, and solution uniqueness detection.

Compile the test suite with:

```bash
gcc -Wall -Wextra -Wpedantic tests/test_solver.c src/solver.c -Iinclude -o test_solver
```

Run the tests with:

```bash
./test_solver
```

If all checks pass, the program will display:

```text
All solver tests passed.
```


## 📈 Benchmark

The project includes a dedicated benchmark to compare the basic backtracking solver with the MRV-optimized version.

Compile the benchmark with:

```bash
gcc -Wall -Wextra -Wpedantic tests/benchmark_solver.c src/solver.c -Iinclude -o benchmark_solver
```

Run it with:

```bash
./benchmark_solver
```

The benchmark solves the same reference Sudoku **1,000 times with each algorithm** and reports the average execution time.

A sample run produced:

```text
Basic Backtracking
Assignments: 4208
Backtracks: 4157
Average time: ~0.799 ms

MRV Backtracking
Assignments: 51
Backtracks: 0
Average time: ~0.254 ms
```

Execution times may vary depending on the system and individual run, while the assignment and backtrack counts provide a more consistent comparison of the search behavior.


## 🛠️ Technologies

- **C** — core programming language
- **GCC** — compilation and warning checks
- **Git & GitHub** — version control and project hosting
- **VS Code** — development environment


## 🔮 Future Improvements

Possible future improvements include:

- Displaying an alternative solution when multiple solutions are detected
- Adding more example puzzles with different difficulty levels
- Improving the command-line interface and user interaction
- Expanding the automated test suite


## 📄 License

This project is licensed under the **MIT License**.

See the `LICENSE` file for more information.