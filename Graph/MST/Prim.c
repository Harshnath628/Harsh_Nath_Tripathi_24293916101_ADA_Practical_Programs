#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 5
#define INF 99999

int min_key(int key[], bool mst_set[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (mst_set[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void print_mst(int parent[], int graph[V][V]) {
    int total_cost = 0;
    printf("Edge \tWeight\n");

    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
        total_cost += graph[i][parent[i]];
    }

    printf("\nTotal cost of Minimum Spanning Tree: %d\n", total_cost);
}

void prim_mst(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mst_set[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mst_set[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < V - 1; i++) {
        int u = min_key(key, mst_set);
        mst_set[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mst_set[v] == false &&
                graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    print_mst(parent, graph);
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    printf("Prim's Algorithm for Minimum Spanning Tree\n");
    prim_mst(graph);

    return 0;
}
