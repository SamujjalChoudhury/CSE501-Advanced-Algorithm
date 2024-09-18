#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 4

typedef struct Node {
    int board[N][N];
    int x, y; // Coordinates of the empty space
    int cost;
    struct Node *parent;
} Node;

int is_goal_state(Node *node) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == N-1 && j == N-1) {
                if (node->board[i][j] != 0) {
                    return 0;
                }
            } else if (node->board[i][j] != (i * N) + j + 1) {
                return 0;
            }
        }
    }
    return 1;
}

Node *generate_child(Node *node, int dx, int dy) {
    Node *child = (Node *)malloc(sizeof(Node));
    child->parent = node;
    child->cost = node->cost + 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            child->board[i][j] = node->board[i][j];
        }
    }

    child->board[node->x][node->y] = child->board[node->x + dx][node->y + dy];
    child->board[node->x + dx][node->y + dy] = 0;
    child->x = node->x + dx;
    child->y = node->y + dy;

    return child;
}

int manhattan_distance(Node *node) {
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int value = node->board[i][j];
            if (value != 0) {
                int goal_i = (value - 1) / N;
                int goal_j = (value - 1) % N;
                distance += abs(i - goal_i) + abs(j - goal_j);
            }
        }
    }
    return distance;
}

// Count inversions in the puzzle board
int count_inversions(int board[N][N]) {
    int inversions = 0;
    int flattened[N * N];
    int k = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0) {
                flattened[k++] = board[i][j];
            }
        }
    }

    for (int i = 0; i < k - 1; i++) {
        for (int j = i + 1; j < k; j++) {
            if (flattened[i] > flattened[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}

int is_solvable(Node *node) {
    int inversions = count_inversions(node->board);

    if (N % 2 == 1) {
        return (inversions % 2 == 0);
    } else {
        int blank_row_from_bottom = N - node->x;
        if (blank_row_from_bottom % 2 == 0) {
            return (inversions % 2 == 1);
        } else {
            return (inversions % 2 == 0);
        }
    }
}

void print_puzzle(Node *node) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", node->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Node *solve_15_puzzle(Node *initial_state) {
    Node *best_solution = NULL;
    int best_cost = INT_MAX;

    Node *queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = initial_state;

    while (front != rear) {
        Node *current = queue[front++];

        if (current->cost >= best_cost) {
            continue;
        }

        if (is_goal_state(current)) {
            if (current->cost < best_cost) {
                best_solution = current;
                best_cost = current->cost;
            }
        } else {
            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};

            for (int i = 0; i < 4; i++) {
                int new_x = current->x + dx[i];
                int new_y = current->y + dy[i];
                if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < N) {
                    Node *child = generate_child(current, dx[i], dy[i]);
                    child->cost += manhattan_distance(child);
                    queue[rear++] = child;
                }
            }
        }
    }

    return best_solution;
}

int main() {
    Node initial_state;

    // testcase 1
    // initial_state.x = 2;
    // initial_state.y = 1;
    // initial_state.cost = 0;
    // initial_state.board[0][0] = 1;
    // initial_state.board[0][1] = 2;
    // initial_state.board[0][2] = 3;
    // initial_state.board[0][3] = 4;
    // initial_state.board[1][0] = 5;
    // initial_state.board[1][1] = 6;
    // initial_state.board[1][2] = 7;
    // initial_state.board[1][3] = 8;
    // initial_state.board[2][0] = 9;
    // initial_state.board[2][1] = 0;
    // initial_state.board[2][2] = 10;
    // initial_state.board[2][3] = 12;
    // initial_state.board[3][0] = 13;
    // initial_state.board[3][1] = 14;
    // initial_state.board[3][2] = 11;
    // initial_state.board[3][3] = 15;

    // testcase 2
    // initial_state.x = 1;
    // initial_state.y = 1;
    // initial_state.board[0][0] = 1;
    // initial_state.board[0][1] = 2;
    // initial_state.board[0][2] = 3;
    // initial_state.board[0][3] = 4;
    // initial_state.board[1][0] = 5;
    // initial_state.board[1][1] = 0;
    // initial_state.board[1][2] = 6;
    // initial_state.board[1][3] = 8;
    // initial_state.board[2][0] = 9;
    // initial_state.board[2][1] = 10;
    // initial_state.board[2][2] = 7;
    // initial_state.board[2][3] = 12;
    // initial_state.board[3][0] = 13;
    // initial_state.board[3][1] = 14;
    // initial_state.board[3][2] = 11;
    // initial_state.board[3][3] = 15;

    // testcase 3
    initial_state.x = 1;
    initial_state.y = 2;
    initial_state.board[0][0] = 1;
    initial_state.board[0][1] = 2;
    initial_state.board[0][2] = 3;
    initial_state.board[0][3] = 4;
    initial_state.board[1][0] = 5;
    initial_state.board[1][1] = 6;
    initial_state.board[1][2] = 0;
    initial_state.board[1][3] = 8;
    initial_state.board[2][0] = 9;
    initial_state.board[2][1] = 10;
    initial_state.board[2][2] = 7;
    initial_state.board[2][3] = 12;
    initial_state.board[3][0] = 13;
    initial_state.board[3][1] = 14;
    initial_state.board[3][2] = 11;
    initial_state.board[3][3] = 15;

    // testcase 4
    // initial_state.x = 0;
    // initial_state.y = 1;
    // initial_state.board[0][0] = 1;
    // initial_state.board[0][1] = 0;
    // initial_state.board[0][2] = 3;
    // initial_state.board[0][3] = 4;
    // initial_state.board[1][0] = 5;
    // initial_state.board[1][1] = 2;
    // initial_state.board[1][2] = 6;
    // initial_state.board[1][3] = 8;
    // initial_state.board[2][0] = 9;
    // initial_state.board[2][1] = 10;
    // initial_state.board[2][2] = 7;
    // initial_state.board[2][3] = 12;
    // initial_state.board[3][0] = 13;
    // initial_state.board[3][1] = 14;
    // initial_state.board[3][2] = 11;
    // initial_state.board[3][3] = 15;

    // testcase 5
    // initial_state.x = 2;
    // initial_state.y = 3;
    // initial_state.board[0][0] = 1;
    // initial_state.board[0][1] = 2;
    // initial_state.board[0][2] = 3;
    // initial_state.board[0][3] = 4;
    // initial_state.board[1][0] = 5;
    // initial_state.board[1][1] = 6;
    // initial_state.board[1][2] = 7;
    // initial_state.board[1][3] = 8;
    // initial_state.board[2][0] = 9;
    // initial_state.board[2][1] = 10;
    // initial_state.board[2][2] = 11;
    // initial_state.board[2][3] = 0;
    // initial_state.board[3][0] = 13;
    // initial_state.board[3][1] = 14;
    // initial_state.board[3][2] = 15;
    // initial_state.board[3][3] = 12;




    if (!is_solvable(&initial_state)) {
        printf("The puzzle is unsolvable.\n");
        return 0;
    }

    Node *solution = solve_15_puzzle(&initial_state);

    if (solution) {
        printf("Initial state:\n");
        print_puzzle(&initial_state);

        printf("Final state:\n");
        print_puzzle(solution);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
