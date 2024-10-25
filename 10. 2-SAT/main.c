#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 10000  // Maximum number of variables
#define MAXM 20000  // Maximum number of clauses

int n;  // Number of variables
int **graph, **reverse_graph;
int *graph_size, *reverse_graph_size;
int *order, order_index;
int *scc, *visited;
int *assignment;  // Solution assignment

// Dynamically allocate a 2D array for the graph
int** allocate_graph(int size) {
    int** graph = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        graph[i] = (int *) malloc(size * sizeof(int));
    }
    return graph;
}

// Add an edge from u to v in the graph and reverse graph
void add_edge(int u, int v) {
    graph[u][graph_size[u]++] = v;
    reverse_graph[v][reverse_graph_size[v]++] = u;
}

// Map variable x to graph index (0-based, positive for x, odd for ¬x)
int var_index(int x) {
    return 2 * (abs(x) - 1) + (x < 0);
}

// First DFS to fill the finishing order
void dfs1(int u) {
    visited[u] = 1;
    for (int i = 0; i < graph_size[u]; i++) {
        int v = graph[u][i];
        if (!visited[v]) {
            dfs1(v);
        }
    }
    order[order_index++] = u;
}

// Second DFS to find SCCs
void dfs2(int u, int component_id) {
    visited[u] = 1;
    scc[u] = component_id;
    for (int i = 0; i < reverse_graph_size[u]; i++) {
        int v = reverse_graph[u][i];
        if (!visited[v]) {
            dfs2(v, component_id);
        }
    }
}

// 2-SAT solver
bool two_sat(int n, int clauses[][2], int m) {
    // Initialize graph sizes
    for (int i = 0; i < 2 * n; i++) {
        graph_size[i] = reverse_graph_size[i] = 0;
    }
    
    // Build the implication graph
    for (int i = 0; i < m; i++) {
        int a = clauses[i][0], b = clauses[i][1];
        add_edge(var_index(-a), var_index(b));  // ¬a -> b
        add_edge(var_index(-b), var_index(a));  // ¬b -> a
    }

    // Step 1: Perform the first DFS to get the finishing order
    order_index = 0;
    for (int i = 0; i < 2 * n; i++) visited[i] = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (!visited[i]) dfs1(i);
    }

    // Step 2: Perform the second DFS on the reverse graph to find SCCs
    for (int i = 0; i < 2 * n; i++) visited[i] = 0;
    int component_id = 0;
    for (int i = order_index - 1; i >= 0; i--) {
        int u = order[i];
        if (!visited[u]) dfs2(u, component_id++);
    }

    // Step 3: Check for contradictions
    for (int i = 0; i < n; i++) {
        if (scc[2 * i] == scc[2 * i + 1]) {
            return false;  // Unsatisfiable
        }
    }

    // Step 4: Assign truth values based on SCCs
    for (int i = 0; i < n; i++) {
        assignment[i] = scc[2 * i] > scc[2 * i + 1];  // x is true if x's SCC > ¬x's SCC
    }

    return true;  // Satisfiable
}

int main() {
    int m;  // Number of clauses

    printf("Enter number of variables and clauses: ");
    scanf("%d %d", &n, &m);

    // Dynamic memory allocation
    graph = allocate_graph(2 * n);
    reverse_graph = allocate_graph(2 * n);
    graph_size = (int*) malloc(2 * n * sizeof(int));
    reverse_graph_size = (int*) malloc(2 * n * sizeof(int));
    order = (int*) malloc(2 * n * sizeof(int));
    scc = (int*) malloc(2 * n * sizeof(int));
    visited = (int*) malloc(2 * n * sizeof(int));
    assignment = (int*) malloc(n * sizeof(int));

    int clauses[m][2];  // Array to store the clauses
    printf("Enter the clauses in the form (a b) for each (a ∨ b):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &clauses[i][0], &clauses[i][1]);
    }

    if (two_sat(n, clauses, m)) {
        printf("Satisfiable\n");
    } else {
        printf("Unsatisfiable\n");
    }

    // Free allocated memory
    for (int i = 0; i < 2 * n; i++) {
        free(graph[i]);
        free(reverse_graph[i]);
    }
    free(graph);
    free(reverse_graph);
    free(graph_size);
    free(reverse_graph_size);
    free(order);
    free(scc);
    free(visited);
    free(assignment);

    return 0;
}