#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int minSteps(int m, int n, int d) {
    if (d > (m > n ? m : n)) return -1;

    int q[10000][3], front = 0, rear = 0;
    bool visited[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            visited[i][j] = false;
        }
    }

    q[rear][0] = 0;
    q[rear][1] = 0;
    q[rear][2] = 0;
    rear++;
    visited[0][0] = true;

    while (front != rear) {
        int jug1 = q[front][0];
        int jug2 = q[front][1];
        int steps = q[front][2];
        front++;

        if (jug1 == d || jug2 == d) return steps;

        if (!visited[m][jug2]) {
            visited[m][jug2] = true;
            q[rear][0] = m;
            q[rear][1] = jug2;
            q[rear][2] = steps + 1;
            rear++;
        }

        if (!visited[jug1][n]) {
            visited[jug1][n] = true;
            q[rear][0] = jug1;
            q[rear][1] = n;
            q[rear][2] = steps + 1;
            rear++;
        }

        if (!visited[0][jug2]) {
            visited[0][jug2] = true;
            q[rear][0] = 0;
            q[rear][1] = jug2;
            q[rear][2] = steps + 1;
            rear++;
        }

        if (!visited[jug1][0]) {
            visited[jug1][0] = true;
            q[rear][0] = jug1;
            q[rear][1] = 0;
            q[rear][2] = steps + 1;
            rear++;
        }

        int pour1to2 = jug1 < (n - jug2) ? jug1 : (n - jug2);
        if (!visited[jug1 - pour1to2][jug2 + pour1to2]) {
            visited[jug1 - pour1to2][jug2 + pour1to2] = true;
            q[rear][0] = jug1 - pour1to2;
            q[rear][1] = jug2 + pour1to2;
            q[rear][2] = steps + 1;
            rear++;
        }

        int pour2to1 = jug2 < (m - jug1) ? jug2 : (m - jug1);
        if (!visited[jug1 + pour2to1][jug2 - pour2to1]) {
            visited[jug1 + pour2to1][jug2 - pour2to1] = true;
            q[rear][0] = jug1 + pour2to1;
            q[rear][1] = jug2 - pour2to1;
            q[rear][2] = steps + 1;
            rear++;
        }
    }

    return -1;
}

int main() {
    int m = 4, n = 3, d = 2;
    // int m = 5, n = 3, d = 4;
    int result = minSteps(m, n, d);

    if (result == -1) {
        printf("Solution not possible\n");
        return 1;
    }

    printf("Minimum number of steps: %d\n", result);
    return 0;
}