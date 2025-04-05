#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DELAY 500000 

int **allocateGrid(int rows, int cols) {
    int **grid = (int **)malloc(rows * sizeof(int *));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed for grid.\n");
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        grid[i] = (int *)malloc(cols * sizeof(int));
        if (grid[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d.\n", i);
            for (int k = 0; k < i; k++) {
                free(grid[k]);
            }
            free(grid);
            return NULL;
        }
    }
    return grid;
}
void freeGrid(int **grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}
void initializeGrid(int **grid, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}
void printGrid(int **grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j] ? '@' : '.');
        }
        printf("\n");
    }
    printf("\n");
}
int countNeighbors(int **grid, int rows, int cols, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int r = x + i;
            int c = y + j;
            if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == 1) {
                count++;
            }
        }
    }
    return count;
}
void nextGeneration(int **grid, int **newGrid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = countNeighbors(grid, rows, cols, i, j);
            if (grid[i][j] == 1) { 
                newGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else { 
                newGrid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
}


int main() {
    int rows, cols, num_iterations;

    printf("Enter the number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        fprintf(stderr, "Invalid input for rows.\n");
        return 1;
    }
    printf("Enter the number of columns: ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        fprintf(stderr, "Invalid input for columns.\n");
        return 1;
    }
    printf("Enter the number of iterations: ");
    if (scanf("%d", &num_iterations) != 1 || num_iterations <= 0) {
        fprintf(stderr, "Invalid input for iterations.\n");
        return 1;
    }


    
    int **grid = allocateGrid(rows, cols);
    int **newGrid = allocateGrid(rows, cols);

    if (grid == NULL || newGrid == NULL) {
        return 1; 
    }

    initializeGrid(grid, rows, cols);

    
    for (int iteration = 0; iteration < num_iterations; iteration++) {
        system("clear"); 
        printGrid(grid, rows, cols);
        nextGeneration(grid, newGrid, rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid[i][j] = newGrid[i][j];
            }
        }
        usleep(DELAY);
    }
    freeGrid(grid, rows);
    freeGrid(newGrid, rows);

    return 0;
}
    