#include <stdio.h>
#include <stdlib.h>

int** createMatrix(int rows, int cols)
{
    int** arr = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) 
    {
        arr[i] = (int*)malloc(cols * sizeof(int));
    }
    return arr;
}

void swapRows(int** matrix, int cols, int row1, int row2)
{
    int *temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;           
}

void scaleRow(int** matrix, int cols, int row, int sc_factor)
{
    for (int i =0; i < cols; i++)
    {
        matrix[row][i] *= sc_factor;  
    }
}

void addScaledRow(int** matrix, int cols, int row1, int row2, int sc_factor)
{
    for (int i =0; i < cols; i++)
    {
        matrix[row1][i] *= sc_factor;
        matrix[row2][i] += matrix[row2][i];
        matrix[row1][i] /= sc_factor;
    }

}

int findRowWithMinSum(int** matrix, int rows, int cols)
{
    int sum[rows];
    int no_sum = 0;
    for (int i =0; i < rows; i++)
    {
        for (int j=0; j < cols; j++)
        {
            sum[no_sum] = sum[no_sum] + matrix[i][j];
        }
        no_sum++;
    }
    int minimum = 1000;
    for (int i = 0; i < rows; i++)
    {
        if (sum[i] < minimum)
        {
            minimum = sum[i];
        }
    }
    return minimum;
}

int** removeRow(int** matrix, int* rows, int cols, int rowToRemove)
{

    for (int i =rowToRemove; i < *rows; i++)
    {
        for( int j =0; j < cols; j++)
        {
            matrix[i][j] = matrix[i + 1][j+1];
        }
    }
    free(matrix[*rows]);
    rows--;
}

void freeMatrix(int** matrix, int rows)
{
    for (int i =0; i < rows; i++)
    {
        free(matrix[i]);
    }
}


/* ------- DO NOT MODIFY BELOW ------- */

void runTestsForMatrixFunctions(){
    int totalMarks = 0, tempMarks = 0, success = 0;

    // Test createMatrix()
    success = 1;
    int rows = 2, cols = 3;
    int **mat = createMatrix(rows, cols);
    if(!mat){
        success = 0;
    } else {
        for(int i = 0; i < rows && success; i++){
            for(int j = 0; j < cols; j++){
                if(mat[i][j] != 0){
                    success = 0;
                    break;
                }
            }
        }
    }
    if(success){
        tempMarks = 10;
        printf("\033[0;32mcreateMatrix() creates and initializes correctly: %d/10\033[0m\n", tempMarks);
    } else {
        printf("\033[0;31mcreateMatrix() creates and initializes correctly: %d/10\033[0m\n", tempMarks);
    }
    totalMarks += tempMarks;
    tempMarks = 0;

    // Test swapRows()
    success = 1;
    if(!mat){
        success = 0;
    } else {
        // Fill first row with 1s, second with 2s
        for(int j = 0; j < cols; j++){
            mat[0][j] = 1;
            mat[1][j] = 2;
        }
        swapRows(mat, cols, 0, 1);
        // Check swapped
        for(int j = 0; j < cols; j++){
            if(mat[0][j] != 2 || mat[1][j] != 1){
                success = 0;
                break;
            }
        }
        // Ensure no spurious changes
        // (implies other rows would remain the same if we had more)
    }
    if(success){
        tempMarks = 5;
        printf("\033[0;32mswapRows() works: %d/5\033[0m\n", tempMarks);
    } else {
        printf("\033[0;31mswapRows() works: %d/5\033[0m\n", tempMarks);
    }
    totalMarks += tempMarks;
    tempMarks = 0;

    // Test scaleRow()
    success = 1;
    if(!mat){
        success = 0;
    } else {
        // Reset row 0 with 1s
        for(int j = 0; j < cols; j++){
            mat[0][j] = 1;
        }
        scaleRow(mat, cols, 0, 3);
        for(int j = 0; j < cols; j++){
            if(mat[0][j] != 3){
                success = 0;
                break;
            }
        }
    }
    if(success){
        tempMarks = 5;
        printf("\033[0;32mscaleRow() works: %d/5\033[0m\n", tempMarks);
    } else {
        printf("\033[0;31mscaleRow() works: %d/5\033[0m\n", tempMarks);
    }
    totalMarks += tempMarks;
    tempMarks = 0;

    // Test addScaledRow()
    success = 1;
    if(!mat){
        success = 0;
    } else {
        // row0 = all 1s, row1 = all 2s
        for(int j = 0; j < cols; j++){
            mat[0][j] = 1;
            mat[1][j] = 2;
        }
        addScaledRow(mat, cols, 0, 1, 2);
        // row1 should become row1 + 2*row0
        for(int j = 0; j < cols; j++){
            int expected = 2 + 2*1; // 2 + 2 = 4
            if(mat[1][j] != expected){
                success = 0;
                break;
            }
            // row0 should still be 1
            if(mat[0][j] != 1){
                success = 0;
                break;
            }
        }
    }
    if(success){
        tempMarks = 5;
        printf("\033[0;32maddScaledRow() works: %d/5\033[0m\n", tempMarks);
    } else {
        printf("\033[0;31maddScaledRow() works: %d/5\033[0m\n", tempMarks);
    }
    totalMarks += tempMarks;
    tempMarks = 0;

    // Test removeRow()
    success = 1;
    // Prepare a 3x3 matrix with distinct row values for easy checks
    freeMatrix(mat, rows);
    rows = 3; cols = 3;
    mat = createMatrix(rows, cols);
    if(!mat){
        success = 0;
    } else {
        // Fill row0 -> 1, row1 -> 2, row2 -> 3
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                mat[i][j] = i + 1;
            }
        }
        // Store old pointer for potential reallocation check
        int** oldMatrix = mat;
        // Remove the middle row (row1)
        mat = removeRow(mat, &rows, cols, 1);
        // Ensure none of the row pointers in the resized array are NULL
        for (int i = 0; i < rows && success; i++){
            if(mat[i] == NULL){
                success = 0;
                break;
            }
        }
        // Check if matrix pointer is valid and rows count is updated
        if(!mat || rows != 2){
            success = 0;
        } else {
            // row0 should be all 1, row1 should be all 3 (old row2 becomes new row1)
            for(int j = 0; j < cols && success; j++){
                if(mat[0][j] != 1 || mat[1][j] != 3){
                    success = 0;
                    break;
                }
            }
        }
    }
    if(success){
        tempMarks = 15;
        printf("\033[0;32mremoveRow() works and resizes correctly: %d/15\033[0m\n", tempMarks);
    } else {
        printf("\033[0;31mremoveRow() works and resizes correctly: %d/15\033[0m\n", tempMarks);
    }
    totalMarks += tempMarks;
    tempMarks = 0;


    // Test findRowWithMinSum()
    success = 1;
    // now mat is 3x2 - fill with some pattern to find min
    int rowSums[3] = {0};
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mat[i][j] = i + (j+1);
            rowSums[i] += mat[i][j];
        }
    }
    int minRow = findRowWithMinSum(mat, rows, cols);
    // We'll just assume row 0 has sum 1+2=3, row1 sum 2+2=4, row2 sum 3+2=5 => min is row0
    if(minRow != 0){
        success = 0;
    }
    // Tie-scenario suggestion: We might return the first row among ties for minimum
    // We'll not deduct marks for tie preference, but we can check if function is consistent

    if(success){
        tempMarks = 15;
        printf("\033[0;32mfindRowWithMinSum() works: %d/15\033[0m\n", tempMarks);
    } else {
        printf("\033[0;31mfindRowWithMinSum() works: %d/15\033[0m\n", tempMarks);
    }
    totalMarks += tempMarks;

    // Test freeMatrix()
    printf("\033[0;36mfreeMatrix() to be manually checked by TAs: ?/5\033[0m\n");
    freeMatrix(mat, rows);
    mat = NULL;

    if(totalMarks == 55){
        printf("\033[0;32mTotal Marks (Matrix Tests): %d/55\033[0m\n", totalMarks);
    } else {
        printf("\033[0;31mTotal Marks (Matrix Tests): %d/55\033[0m\n", totalMarks);
    }
}

int main(){
    printf("\033[1m\033[35mRunning Matrix Tests...\033[0m\n");
    runTestsForMatrixFunctions();
    return 0;
}