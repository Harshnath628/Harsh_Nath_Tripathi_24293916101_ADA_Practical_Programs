#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

// ----------- Node for Adjacency List -------------
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj_list[MAX_VERTICES] = {NULL};

// Create a new adjacency list node
Node* create_node(int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

// Add edge in adjacency list
void add_edge_to_list(int src, int dest) {
    Node* new_node = create_node(dest);
    new_node->next = adj_list[src];
    adj_list[src] = new_node;
}

// ----------- Queue for BFS -------------
int queue[MAX_VERTICES];
int front = -1, rear = -1;

void enqueue(int data) {
    if (rear == MAX_VERTICES - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = data;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

// ----------- BFS Implementation -------------
void bfs(int start_node, int num_vertices) {
    int visited[MAX_VERTICES] = {0};
    Node* temp;

    front = rear = -1;

    printf("\n==================================\n");
    printf("      B R E A D T H - F I R S T   S E A R C H\n");
    printf("==================================\n");

    enqueue(start_node);
    visited[start_node] = 1;

    printf("BFS Traversal starting from Vertex %d: ", start_node);

    while (front != -1 && front <= rear) {
        int current = dequeue();
        printf("%d ", current);

        temp = adj_list[current];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                enqueue(neighbor);
            }
            temp = temp->next;
        }
    }
    printf("\n");

    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i]) {
            printf("Note: Graph is disconnected → Vertex %d was not reached.\n", i);
        }
    }
}

// ----------- Input Graph -------------
void input_graph(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int *num_vertices, int graph_type) {
    int i, j, num_edges, src, dest;

    printf("Enter the number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", num_vertices);

    if (*num_vertices <= 0 || *num_vertices > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        exit(1);
    }

    // Initialize matrix
    for (i = 0; i < *num_vertices; i++)
        for (j = 0; j < *num_vertices; j++)
            adj_matrix[i][j] = 0;

    printf("Enter the number of edges: ");
    scanf("%d", &num_edges);

    printf("Enter each edge (src dest) from 0 to %d:\n", *num_vertices - 1);

    for (i = 0; i < num_edges; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);

        if (src < 0 || src >= *num_vertices || dest < 0 || dest >= *num_vertices) {
            printf("Invalid vertex index. Skipping.\n");
            continue;
        }

        adj_matrix[src][dest] = 1;
        add_edge_to_list(src, dest);

        if (graph_type == 0) {
            adj_matrix[dest][src] = 1;
            add_edge_to_list(dest, src);
        }
    }
}

// ----------- Display Adjacency Matrix -------------
void display_matrix(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int n) {
    printf("\n==================================\n");
    printf("      A D J A C E N C Y   M A T R I X\n");
    printf("==================================\n");

    printf("   ");
    for (int i = 0; i < n; i++) printf("%d ", i);
    printf("\n---");

    for (int i = 0; i < n; i++) printf("--");
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d | ", i);
        for (int j = 0; j < n; j++)
            printf("%d ", adj_matrix[i][j]);
        printf("\n");
    }
}

// ----------- Display Adjacency List -------------
void display_list(int n) {
    printf("\n==================================\n");
    printf("       A D J A C E N C Y   L I S T\n");
    printf("==================================\n");

    for (int i = 0; i < n; i++) {
        printf("Vertex %d:", i);
        Node* temp = adj_list[i];
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices, choice, start;

    printf("Select Graph Type:\n");
    printf("0. Undirected Graph\n");
    printf("1. Directed Graph\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int graph_type = (choice == 1) ? 1 : 0;

    input_graph(adj_matrix, &num_vertices, graph_type);

    display_matrix(adj_matrix, num_vertices);
    display_list(num_vertices);

    printf("\nEnter starting vertex for BFS (0 to %d): ", num_vertices - 1);
    scanf("%d", &start);

    if (start >= 0 && start < num_vertices)
        bfs(start, num_vertices);
    else
        printf("Invalid start node.\n");

    // Free adjacency list memory
    for (int i = 0; i < num_vertices; i++) {
        Node *curr = adj_list[i], *next;
        while (curr) {
            next = curr->next;
            free(curr);
            curr = next;
        }
    }

    return 0;
}
