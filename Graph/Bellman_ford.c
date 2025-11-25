#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 50
#define INF INT_MAX

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int V, E;
    Edge edges[MAX_VERTICES * MAX_VERTICES];
} Graph;

void printDistances(long long dist[], int V) {
    printf("\nVertex\tDistance\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) printf("%d\tINF\n", i);
        else printf("%d\t%lld\n", i, dist[i]);
    }
}

void bellmanFord(Graph* g, int start) {
    int V = g->V;
    int E = g->E;
    long long dist[V];

    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[start] = 0;

    for (int i = 1; i <= V - 1; i++)
        for (int j = 0; j < E; j++) {
            int u = g->edges[j].src;
            int v = g->edges[j].dest;
            int w = g->edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }

    for (int j = 0; j < E; j++) {
        int u = g->edges[j].src;
        int v = g->edges[j].dest;
        int w = g->edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("\nERROR: Negative weight cycle detected!\n");
            return;
        }
    }

    printf("\nBellman-Ford Result:\n");
    printDistances(dist, V);
}

int main() {
    Graph g;
    int V, E, s, d, w;

    printf("Enter vertices: ");
    scanf("%d", &V);

    printf("Enter edges: ");
    scanf("%d", &E);

    g.V = V;
    g.E = E;

    for (int i = 0; i < E; i++) {
        printf("Edge %d (src dest weight): ", i + 1);
        scanf("%d %d %d", &s, &d, &w);
        g.edges[i] = (Edge){s, d, w};
    }

    int start;
    printf("Enter start node: ");
    scanf("%d", &start);

    bellmanFord(&g, start);
    return 0;
}
