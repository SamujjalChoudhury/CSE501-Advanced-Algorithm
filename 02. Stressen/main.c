#include <stdio.h>
#include <stdlib.h>

void addMatrices(int size, int A[size][size], int B[size][size], int result[size][size]);
void subtractMatrices(int size, int A[size][size], int B[size][size], int result[size][size]);
void multiplyMatrices(int size, int A[size][size], int B[size][size], int C[size][size]);

void printMatrix(int size, int matrix[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

void splitMatrix(int size, int A[size][size], int A11[size/2][size/2], int A12[size/2][size/2], int A21[size/2][size/2], int A22[size/2][size/2]) {
    int newSize = size / 2;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
        }
    }
}

void combineMatrix(int size, int C11[size/2][size/2], int C12[size/2][size/2], int C21[size/2][size/2], int C22[size/2][size/2], int C[size][size]) {
    int newSize = size / 2;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

void multiplyMatrices(int size, int A[size][size], int B[size][size], int C[size][size]) {
    if (size == 2) {
        int m1, m2, m3, m4, m5, m6, m7;
        int A11 = A[0][0], A12 = A[0][1], A21 = A[1][0], A22 = A[1][1];
        int B11 = B[0][0], B12 = B[0][1], B21 = B[1][0], B22 = B[1][1];

        m1 = (A11 + A22) * (B11 + B22);
        m2 = (A21 + A22) * B11;
        m3 = A11 * (B12 - B22);
        m4 = A22 * (B21 - B11);
        m5 = (A11 + A12) * B22;
        m6 = (A21 - A11) * (B11 + B12);
        m7 = (A12 - A22) * (B21 + B22);

        C[0][0] = m1 + m4 - m5 + m7;
        C[0][1] = m3 + m5;
        C[1][0] = m2 + m4;
        C[1][1] = m1 - m2 + m3 + m6;
        return;
    }

    int newSize = size / 2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
    int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize];
    int M5[newSize][newSize], M6[newSize][newSize], M7[newSize][newSize];
    int tempA[newSize][newSize], tempB[newSize][newSize];

    splitMatrix(size, A, A11, A12, A21, A22);
    splitMatrix(size, B, B11, B12, B21, B22);

    addMatrices(newSize, A11, A22, tempA);
    addMatrices(newSize, B11, B22, tempB);
    multiplyMatrices(newSize, tempA, tempB, M1);

    addMatrices(newSize, A21, A22, tempA);
    multiplyMatrices(newSize, tempA, B11, M2);

    subtractMatrices(newSize, B12, B22, tempB);
    multiplyMatrices(newSize, A11, tempB, M3);

    subtractMatrices(newSize, B21, B11, tempB);
    multiplyMatrices(newSize, A22, tempB, M4);

    addMatrices(newSize, A11, A12, tempA);
    multiplyMatrices(newSize, tempA, B22, M5);

    subtractMatrices(newSize, A21, A11, tempA);
    addMatrices(newSize, B11, B12, tempB);
    multiplyMatrices(newSize, tempA, tempB, M6);

    subtractMatrices(newSize, A12, A22, tempA);
    addMatrices(newSize, B21, B22, tempB);
    multiplyMatrices(newSize, tempA, tempB, M7);

    addMatrices(newSize, M1, M4, tempA);
    subtractMatrices(newSize, tempA, M5, tempB);
    addMatrices(newSize, tempB, M7, C11);

    addMatrices(newSize, M3, M5, C12);
    addMatrices(newSize, M2, M4, C21);
    addMatrices(newSize, M1, M3, tempA);
    subtractMatrices(newSize, tempA, M2, tempB);
    addMatrices(newSize, tempB, M6, C22);

    combineMatrix(size, C11, C12, C21, C22, C);
}

void addMatrices(int size, int A[size][size], int B[size][size], int result[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrices(int size, int A[size][size], int B[size][size], int result[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

int main() {
    int size = 4; // For 4x4 matrices
    int x[size][size];
    int y[size][size];
    int z[size][size];

    printf("Enter the elements of the first 4x4 matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &x[i][j]);
        }
    }

    printf("Enter the elements of the second 4x4 matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &y[i][j]);
        }
    }

    multiplyMatrices(size, x, y, z);

    printf("Product achieved using Strassen's algorithm:\n");
    printMatrix(size, z);

    return 0;
}


// SamujjalChoudhury
