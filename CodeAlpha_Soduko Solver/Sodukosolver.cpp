#include <iostream>
#include <array>
#include <limits>

using namespace std;

class SudokuSolver {
private:
    static const int SIZE = 9;
    using Grid = array<array<int, SIZE>, SIZE>;

    Grid board{}; // 2D Sudoku grid

    // ---------------- Utility Functions ----------------

    // Check if num exists in given row
    bool isRowValid(int row, int num) const {
        for (int col = 0; col < SIZE; ++col)
            if (board[row][col] == num)
                return false;
        return true;
    }

    // Check if num exists in given column
    bool isColValid(int col, int num) const {
        for (int row = 0; row < SIZE; ++row)
            if (board[row][col] == num)
                return false;
        return true;
    }

    // Check if num exists in 3x3 subgrid
    bool isBoxValid(int startRow, int startCol, int num) const {
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                if (board[startRow + r][startCol + c] == num)
                    return false;
        return true;
    }

    // Combined safety check
    bool isSafe(int row, int col, int num) const {
        return isRowValid(row, num) &&
               isColValid(col, num) &&
               isBoxValid(row - row % 3, col - col % 3, num);
    }

    // Find next empty cell (0 represents empty)
    bool findEmptyCell(int &row, int &col) const {
        for (row = 0; row < SIZE; ++row)
            for (col = 0; col < SIZE; ++col)
                if (board[row][col] == 0)
                    return true;
        return false;
    }

public:
    // ---------------- Input ----------------

    void readInput() {
        cout << "Enter Sudoku grid (9x9).\n";
        cout << "Use 0 for empty cells.\n\n";

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                while (true) {
                    cout << "Enter value for cell [" << i << "][" << j << "]: ";
                    cin >> board[i][j];

                    if (cin.fail() || board[i][j] < 0 || board[i][j] > 9) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number (0-9).\n";
                    } else {
                        break;
                    }
                }
            }
        }
    }

    // ---------------- Display ----------------

    void printBoard() const {
        cout << "\n-------------------------\n";
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (j % 3 == 0) cout << "| ";
                cout << board[i][j] << " ";
            }
            cout << "|\n";
            if ((i + 1) % 3 == 0)
                cout << "-------------------------\n";
        }
    }

    // ---------------- Validation ----------------

    bool isInitialBoardValid() const {
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                int num = board[row][col];

                if (num != 0) {
                    // Temporarily remove the number
                    Grid temp = board;
                    temp[row][col] = 0;

                    // Check row and column
                    for (int x = 0; x < SIZE; ++x)
                        if (temp[row][x] == num || temp[x][col] == num)
                            return false;

                    // Check subgrid
                    int startRow = row - row % 3;
                    int startCol = col - col % 3;

                    for (int r = 0; r < 3; ++r)
                        for (int c = 0; c < 3; ++c)
                            if (temp[startRow + r][startCol + c] == num)
                                return false;
                }
            }
        }
        return true;
    }

    // ---------------- Solver (Backtracking) ----------------

    bool solve() {
        int row, col;

        // Base case: no empty cell → solved
        if (!findEmptyCell(row, col))
            return true;

        // Try digits 1–9
        for (int num = 1; num <= 9; ++num) {
            if (isSafe(row, col, num)) {
                board[row][col] = num;

                if (solve()) // recursive call
                    return true;

                board[row][col] = 0; // backtrack
            }
        }

        return false; // trigger backtracking
    }
};

// ---------------- Main ----------------

int main() {
    SudokuSolver solver;

    solver.readInput();

    cout << "\nInput Sudoku:";
    solver.printBoard();

    if (!solver.isInitialBoardValid()) {
        cout << "\n Error: Invalid Sudoku configuration.\n";
        return 1;
    }

    if (solver.solve()) {
        cout << "\n Solved Sudoku:";
        solver.printBoard();
    } else {
        cout << "\n No solution exists.\n";
    }

    return 0;
}