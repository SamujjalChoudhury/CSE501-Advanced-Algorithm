#include <stdio.h>
#include <limits.h>

int MatrixChainOrder(int p[], int i, int j) {
    if (i == j) {
        return 0;
    }

    int min = INT_MAX;

    for (int k = i; k < j; k++) {
        int count = MatrixChainOrder(p, i, k) +
                    MatrixChainOrder(p, k + 1, j) +
                    p[i - 1] * p[k] * p[j];

        if (count < min) {
            min = count;
        }
    }

    return min;
}

int main() {
    int arr[] = {10, 20, 30, 40, 30, 10};
    // int arr[] = {2, 3, 6, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int minCost = MatrixChainOrder(arr, 1, n - 1);

    printf("Minimum number of multiplications is %d\n", minCost);

    return 0;
}
