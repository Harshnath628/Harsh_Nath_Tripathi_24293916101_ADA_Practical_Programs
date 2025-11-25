#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_VERTICES 50
#define INF INT_MAX

// ===================== EDGE LIST GRAPH =======================
typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int V;
    int E;
    Edge edges[MAX_VERTICES * MAX_VERTICES];
} Graph;


// ===================== MIN HEAP DEFINITIONS ===================
typedef struct {
    int v;
    int dist;
} HeapNode;

typedef struct {
    int size;
    int capacity;
    int* pos;
    HeapNode** array;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) {
        perror("Memory allocation failed for MinHeap");
        exit(EXIT_FAILURE);
    }

    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->array = (HeapNode**)malloc(capacity * sizeof(HeapNode*)); // FIXED

    if (!minHeap->pos || !minHeap->array) {
        perror("Memory allocation failed for MinHeap arrays");
        exit(EXIT_FAILURE);
    }

    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

HeapNode* newHeapNode(int v, int dist) {
    HeapNode* node = (HeapNode*)malloc(sizeof(HeapNode));
    node->v = v;
    node->dist = dist;
    return node;
}

void swapHeapNode(HeapNode** a, HeapNode** b) {
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left  = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        HeapNode* smallestNode = minHeap->array[smallest];
        HeapNode* idxNode      = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v]      = smallest;

        swapHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

HeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    HeapNode* root     = minHeap->array[0];
    HeapNode* lastNode = minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;
    minHeap->pos[lastNode->v] = 0;  // FIXED

    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v]             = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v]   = i;

        swapHeapNode(&minHeap->array[i],
                     &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}


// ===================== ADJACENCY LIST GRAPH ===================
typedef struct AdjNode {
    int dest;
    int weight;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    AdjNode* head;
} AdjList;

typedef struct {
    int V;
    AdjList* array;
} AdjGraph;

AdjNode* newAdjNode(int dest, int weight) {
    AdjNode* node = (AdjNode*)malloc(sizeof(AdjNode));
    node->dest   = dest;
    node->weight = weight;
    node->next   = NULL;
    return node;
}

AdjGraph* createAdjGraph(int V) {
    AdjGraph* g = (AdjGraph*)malloc(sizeof(AdjGraph));
    g->V = V;
    g->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++)
        g->array[i].head = NULL;
    return g;
}

void addEdgeToAdjGraph(AdjGraph* g, int src, int dest, int weight) {
    AdjNode* n = newAdjNode(dest, weight);
    n->next = g->array[src].head;
    g->array[src].head = n;
}


// ===================== UTILS =======================
void print_distances(int dist[], int V, const char* algorithm) {
    printf("\n--- %s Results ---\n", algorithm);
    printf("Vertex\tDistance\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, dist[i]);
    }
}


// ===================== DIJKSTRA (ARRAY) ===================
int minDistance_array(int dist[], int visited[], int V) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra_array(Graph* g, int start, int adj_matrix[MAX_VERTICES][MAX_VERTICES]) {
    int V = g->V;
    int dist[MAX_VERTICES], visited[MAX_VERTICES] = {0};

    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance_array(dist, visited, V);

        if (u == -1) break;

        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && adj_matrix[u][v] != INF && dist[u] != INF
                && dist[u] + adj_matrix[u][v] < dist[v]) {

                dist[v] = dist[u] + adj_matrix[u][v];
            }
        }
    }

    print_distances(dist, V, "Dijkstra (Array / O(V^2))");
}


// ===================== DIJKSTRA (MIN-HEAP) ===================
void dijkstra_heap(AdjGraph* g, int start) {
    int V = g->V;
    int dist[MAX_VERTICES];

    for (int i = 0; i < V; i++)
        dist[i] = INF;

    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        minHeap->array[v] = newHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->size = V;
    dist[start] = 0;
    decreaseKey(minHeap, start, 0);

    while (!isEmpty(minHeap)) {
        HeapNode* node = extractMin(minHeap);
        int u = node->v;
        free(node);

        AdjNode* p = g->array[u].head;

        while (p) {
            int v = p->dest;
            int w = p->weight;

            if (isInMinHeap(minHeap, v) && dist[u] != INF &&
                dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;
                decreaseKey(minHeap, v, dist[v]);
            }
            p = p->next;
        }
    }

    print_distances(dist, V, "Dijkstra (Min-Heap / O((V+E) log V))");

    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
}


// ===================== DRIVER ===================
void run_dijkstra(int V, int E, Graph* g, int adj_matrix[MAX_VERTICES][MAX_VERTICES]) {
    int start;
    printf("\nEnter START NODE (0-%d): ", V - 1);
    scanf("%d", &start);

    AdjGraph* adj_graph = createAdjGraph(V);
    for (int i = 0; i < E; i++) {
        addEdgeToAdjGraph(adj_graph, g->edges[i].src,
                                      g->edges[i].dest,
                                      g->edges[i].weight);
    }

    printf("\n=========== Dijkstra Performance Comparison ============\n");

    clock_t t1 = clock();
    dijkstra_array(g, start, adj_matrix);
    clock_t t2 = clock();

    printf("Time (Array): %f sec\n",
           (double)(t2 - t1) / CLOCKS_PER_SEC);

    t1 = clock();
    dijkstra_heap(adj_graph, start);
    t2 = clock();

    printf("Time (Heap):  %f sec\n",
           (double)(t2 - t1) / CLOCKS_PER_SEC);


    // Free adjacency list
    for (int i = 0; i < V; i++) {
        AdjNode* curr = adj_graph->array[i].head;
        while (curr) {
            AdjNode* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(adj_graph->array);
    free(adj_graph);
}


// ===================== MAIN ===================
int main() {
    Graph g;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    int V, E, src, dest, weight;

    printf("Enter number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &V);
    g.V = V;

    printf("Enter number of edges: ");
    scanf("%d", &E);
    g.E = E;

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj_matrix[i][j] = INF;

    for (int i = 0; i < E; i++) {
        printf("Edge %d (src dest weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);

        g.edges[i].src = src;
        g.edges[i].dest = dest;
        g.edges[i].weight = weight;

        adj_matrix[src][dest] = weight;
    }

    run_dijkstra(V, E, &g, adj_matrix);

    return 0;
}
