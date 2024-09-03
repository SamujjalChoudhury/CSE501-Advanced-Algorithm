#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 1000000

int parent[MAX], sz[MAX];

void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            a ^= b ^= a ^= b;  // Swap a and b
        parent[b] = a;
        sz[a] += sz[b];
    }
}

typedef struct {
    int u, v, weight;
} Edge;

int compare_edges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(Edge edges[], int num_edges, int num_vertices, Edge result[], int *mst_weight) {
    for (int i = 0; i < num_vertices; i++) {
        make_set(i);
    }

    qsort(edges, num_edges, sizeof(Edge), compare_edges);

    *mst_weight = 0;
    int count = 0;
    for (int i = 0; i < num_edges && count < num_vertices - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if (find_set(u) != find_set(v)) {
            union_set(u, v);
            result[count++] = edges[i];
            *mst_weight += weight;
        }
    }
}

int creates_cycle(Edge edges[], int num_edges, Edge exclude_edge, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        make_set(i);
    }

    int mst_weight = 0;
    int count = 0;

    for (int i = 0; i < num_edges; i++) {
        if (edges[i].u == exclude_edge.u && edges[i].v == exclude_edge.v && edges[i].weight == exclude_edge.weight) {
            continue;  // Skip the excluded edge
        }

        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if (find_set(u) != find_set(v)) {
            union_set(u, v);
            mst_weight += weight;
            count++;
        }
    }

    return count == num_vertices - 1 ? mst_weight : -1;
}

int find_second_best_mst(Edge edges[], int num_edges, int num_vertices, Edge mst[], int mst_weight) {
    int second_best = INF;

    for (int i = 0; i < num_vertices - 1; i++) {
        Edge exclude_edge = mst[i];
        int weight = creates_cycle(edges, num_edges, exclude_edge, num_vertices);
        if (weight != -1 && weight > mst_weight && weight < second_best) {
            second_best = weight;
        }
    }

    return second_best == INF ? -1 : second_best;
}

int main() {
    // int num_vertices = 5;
    // int num_edges = 7;
    // Edge edges[] = {
    //     {0, 1, 1},
    //     {0, 2, 3},
    //     {1, 2, 3},
    //     {1, 3, 6},
    //     {2, 3, 5},
    //     {2, 4, 2},
    //     {3, 4, 4}
    // };

    int num_vertices = 5;
    int num_edges = 7;
    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 8},
        {1, 2, 5},
        {1, 3, 6},
        {2, 3, 7},
        {2, 4, 12},
        {3, 4, 4}
    };


    Edge mst[MAX];
    int mst_weight;

    kruskal(edges, num_edges, num_vertices, mst, &mst_weight);

    printf("MST edges and weight:\n");
    for (int i = 0; i < num_vertices - 1; i++) {
        printf("%d - %d => %d\n", mst[i].u, mst[i].v, mst[i].weight);
    }
    printf("Total weight of MST: %d\n", mst_weight);

    int second_best_mst_weight = find_second_best_mst(edges, num_edges, num_vertices, mst, mst_weight);

    if (second_best_mst_weight == -1) {
        printf("No second-best MST found.\n");
    } else {
        printf("Total weight of the second-best MST: %d\n", second_best_mst_weight);
    }

    return 0;
}
