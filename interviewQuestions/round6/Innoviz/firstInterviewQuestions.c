#include <stdio.h>
#include <stdint.h>

#define PUBLIC extern
#define NUM_ROWS 5
#define NUM_COLS 6
typedef uint8_t pixelMatrix [NUM_ROWS * NUM_COLS];

struct matrixObject
{
    size_t rows;
    size_t cols;
    pixelMatrix samplePixelMatrix;
};

struct matrixObject sampleMatrixObject = {NUM_ROWS, NUM_COLS};
//pixelMatrix samplePixelMatrix;


// Public APIs
PUBLIC int GetByte(int row, int col)
{
    const char funcName [] = "GetByte - ";
    if ((row < 0 || row >= NUM_ROWS) || (col < 0 || col >= NUM_COLS))
    {
        printf("%s invalid location\n", funcName);
        return -1;
    }
    
    return sampleMatrixObject.samplePixelMatrix[row * sizeof(uint8_t) + col];
}

PUBLIC 

void matrixExample()
{
    const char funcName [] = "matrixExample - ";
    printf("%s - start\n", funcName);
    size_t counter = 0;
    for (uint8_t i = 0; i < NUM_ROWS; ++i)
    {
        for (uint8_t j = 0; j < NUM_COLS; ++j)
        {
            sampleMatrixObject.samplePixelMatrix[(sizeof(uint8_t) * i) + j] = counter++;
        }
    }
    
    int retVal = GetByte(1, 0);
    int expectedRetVal = 6;
    if (retVal != expectedRetVal)
    {
        printf("%s did not get the expected value\n", funcName);
        return;
    }
    
    printf("%s - end\n", funcName);
}



int main()
{
    printf("main - start\n");
    matrixExample();
    printf("main - end\n");
    return 0;
}
