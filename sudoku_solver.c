#include <stdio.h>
#include <stdbool.h>

#define N 9
#define UNASSIGNED 0

bool isSafe(int grid[N][N], int row, int col, int num);

/* Helper function to check if a given digit can be placed in a certain position */
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if 'num' is not already present in the current row and column
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    // Check if 'num' is not present in the current 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    // If 'num' is not present in the current row, column, and subgrid, it's safe to place
    return true;
}

/* Helper function to find an unassigned position in the Sudoku grid */
bool findUnassignedLocation(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++)
        for (*col = 0; *col < N; (*col)++)
            if (grid[*row][*col] == UNASSIGNED)
                return true;
    return false;
}

/* Main recursive function to solve Sudoku using backtracking */
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there is no unassigned location, the Sudoku puzzle is solved
    if (!findUnassignedLocation(grid, &row, &col))
        return true;

    // Try placing numbers 1 to 9 in the current position
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // If placing the number is safe, assign it to the current position
            grid[row][col] = num;

            // Recursively try to solve the rest of the puzzle
            if (solveSudoku(grid))
                return true;

            // If placing the number doesn't lead to a solution, backtrack
            grid[row][col] = UNASSIGNED;
        }
    }

    // If no number can be placed in the current position, backtrack
    return false;
}

/* Function to print the solved Sudoku grid */
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%2d ", grid[row][col]);
        printf("\n");
    }
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    if (solveSudoku(grid) == true)
        printGrid(grid);
    else
        printf("No solution exists\n");

    return 0;
}
