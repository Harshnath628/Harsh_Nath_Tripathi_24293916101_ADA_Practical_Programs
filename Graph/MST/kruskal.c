#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10
#define INF 999

int parent[MAX_VERTICES];
int n;

int find(int i) {
    while (parent[i] != 0) {
        i = parent[i];
    }
    return i;
}

int uni(int i, int j) {
    i = find(i);
    j = find(j);
    if (i != j) {
        parent[j] = i;
        return 1;
    }
    return 0;
}

void kruskal_mst(int cost[MAX_VERTICES][MAX_VERTICES]) {
    int ne = 1;
    int mincost = 0;
    int i, j;

    printf("\n--- Edges of Minimum Cost Spanning Tree ---\n");
    while (ne < n) {
        int min = INF;
        int a = -1, b = -1;
        int u = -1, v = -1;

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (cost[i][j] < min) {
                    min = cost[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }

        u = find(u);
        v = find(v);

        if (uni(u, v)) {
            printf("%d edge (%d, %d) = %d\n", ne++, a, b, min);
            mincost += min;
        }

        cost[a][b] = cost[b][a] = INF;
    }
    printf("\nMinimum cost = %d\n", mincost);
}

int main() {
    int cost[MAX_VERTICES][MAX_VERTICES];
    int i, j;

    for (i = 0; i < MAX_VERTICES; i++) {
        parent[i] = 0;
    }

    printf("Enter the number of vertices (max %d): ", MAX_VERTICES - 1);
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (use %d for no edge):\n", INF);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0) cost[i][j] = INF;
        }
    }

    kruskal_mst(cost);
    return 0;
}
