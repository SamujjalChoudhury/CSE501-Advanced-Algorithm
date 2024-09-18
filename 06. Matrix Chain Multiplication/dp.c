#include <stdio.h>
#include <stdlib.h>

int MatrixChainOrder(int p[], int i, int j, int n, int **m, int **s) {
    if (i == j) {
        return 0;
    }

    if (m[i][j] != -1) {
        return m[i][j];
    }

    int min = 1000000;

    for (int k = i; k < j; k++) {
        int count = MatrixChainOrder(p, i, k, n, m, s) +
                    MatrixChainOrder(p, k + 1, j, n, m, s) +
                    p[i - 1] * p[k] * p[j];

        if (count < min) {
            min = count;
            s[i][j] = k; 
        }
    }

    m[i][j] = min;
    return min;
}

void PrintOptimalParens(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        PrintOptimalParens(s, i, s[i][j]);
        PrintOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 30, 10};
    // int arr[] = {2, 3, 6, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int **m = (int **)malloc(n * sizeof(int *));
    int **s = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        m[i] = (int *)malloc(n * sizeof(int));
        s[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            m[i][j] = -1;
            s[i][j] = 0;
        }
    }

    int minCost = MatrixChainOrder(arr, 1, n - 1, n, m, s);

    printf("Multiplications is %d\n", minCost);

    printf("Order is: ");
    PrintOptimalParens(s, 1, n - 1);
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);

    return 0;
}
