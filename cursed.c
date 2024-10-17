#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int **readcsv(const char *file, int *row, int *column)
{
    FILE *data = fopen(file, "r");
    if (!data)
    {
        perror("invalid File\n");
        return NULL;
    }
    char line[4000];
    int rowcount = 0;
    int columncount = 0;

    while (fgets(line, sizeof(line), data))
    {
        rowcount++;
        if (rowcount == 1)
        {
            char *token = strtok(line, ",");
            while (token)
            {
                columncount++;
                token = strtok(NULL, ",");
            }
        }
    }
    int **matrix = malloc(rowcount * sizeof(int *));
    for (int i = 0; i < rowcount; i++)
    {
        matrix[i] = malloc(columncount * sizeof(int));
    }
    rewind(data);

    int i = 0;
    int j = 0;
    while (fgets(line, sizeof(line), data))
    {
        char *token = strtok(line, ",");
        j = 0;
        while (token)
        {
            matrix[i][j++] = atoi(token);
            token = strtok(NULL, ",");
        }
    }
    fclose(data);
    *row = rowcount;
    *column = columncount;

    return matrix;
}

int **dot(int sizex1, int sizey1, int sizex2, int sizey2, int mat1[sizex1][sizey1], int mat2[sizex2][sizey2])
{
    if (sizey1 != sizex2)
    {
        printf("Invalid Multipication \n");
        return NULL;
    }

    int **sum = malloc(sizex1 * sizeof(int *));
    for (int i = 0; i < sizex1; i++)
    {
        sum[i] = malloc(sizey2 * sizeof(int));
    }

    for (int i = 0; i < sizex1; i++)
    {
        for (int j = 0; j < sizey2; j++)
        {
            sum[i][j] = 0;
            for (int k = 0; k < sizey2; k++)
            {
                sum[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return sum;
}
void free_mat(int **mat, int sizex1)
{
    for (int i = 0; i < sizex1; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

void transpose(int sizex, int sizey, int mat[sizex][sizey])
{
    for (int i = 0; i < sizex; i++)
    {
        for (int j = 0; j < sizey; j++)
        {
            mat[i][j] = mat[j][i];
        }
    }
    return;
}

void printMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int row;
    int column;
    int **data = readcsv("/home/jelly/Downloads/mnist_train.csv", &row, &column);
    printMatrix(data, row, column);
}