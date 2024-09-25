#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

int time = 0;

void addEdge(int adj[MAX][MAX], int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void articulationDFS(int u, bool visited[], int disc[], int low[], int parent[], bool ap[], int adj[MAX][MAX], int V) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {  // If v is an adjacent vertex of u
            if (!visited[v]) {  // v is not visited yet
                children++;
                parent[v] = u;
                articulationDFS(v, visited, disc, low, parent, ap, adj, V);

                // Check if the subtree rooted at v has a connection back to ancestors of u
                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                // u is an articulation point if it's root and has two or more children
                if (parent[u] == -1 && children > 1) {
                    ap[u] = true;
                }

                // u is an articulation point if it's not root and low[v] >= disc[u]
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    ap[u] = true;
                }
            } else if (v != parent[u]) {
                // Update low[u] for back edge
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
            }
        }
    }
}

void findArticulationPoints(int adj[MAX][MAX], int V) {
    bool visited[MAX];   
    int disc[MAX];       
    int low[MAX];        
    int parent[MAX];     
    bool ap[MAX];        

    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        visited[i] = false;
        ap[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            articulationDFS(i, visited, disc, low, parent, ap, adj, V);
        }
    }
    printf("Articulation points are: \n");
    for (int i = 0; i < V; i++) {
        if (ap[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {

    // Case 1
    int V = 5;
    int adj[MAX][MAX] = {0};
    addEdge(adj, 0, 1);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 3, 4);

    // Case 2
    // int V = 7;
    // int adj[MAX][MAX] = {0};
    // addEdge(adj, 0, 1);
    // addEdge(adj, 1, 2);
    // addEdge(adj, 1, 4);
    // addEdge(adj, 2, 3);
    // addEdge(adj, 3, 5);
    // addEdge(adj, 3, 6);
    // addEdge(adj, 4, 5);

    // Case 3
    // int V = 8;
    // int adj[MAX][MAX] = {0};
    // addEdge(adj, 0, 1);
    // addEdge(adj, 0, 2);
    // addEdge(adj, 1, 2);
    // addEdge(adj, 1, 4);
    // addEdge(adj, 1, 6);
    // addEdge(adj, 3, 4);
    // addEdge(adj, 3, 5);
    // addEdge(adj, 4, 6);
    // addEdge(adj, 6, 7);

    findArticulationPoints(adj, V);

    return 0;
}
