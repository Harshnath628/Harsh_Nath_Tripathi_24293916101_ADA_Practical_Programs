#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

// ------------- Adjacency List Node -------------
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj_list[MAX_VERTICES] = {NULL};

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

void add_edge_to_list(int src, int dest) {
    Node* new_node = create_node(dest);
    new_node->next = adj_list[src];
    adj_list[src] = new_node;
}

// ------------- DFS Utility (Recursive) -------------
void dfs_util(int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = adj_list[vertex];
    while (temp != NULL) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            dfs_util(neighbor, visited);
        }
        temp = temp->next;
    }
}

// ------------- DFS Wrapper -------------
void dfs(int start_node, int num_vertices) {
    int visited[MAX_VERTICES] = {0};

    printf("\n==================================\n");
    printf("     D E P T H - F I R S T   S E A R C H\n");
    printf("==================================\n");
    printf("DFS Traversal starting from Vertex %d: ", start_node);

    dfs_util(start_node, visited);
    printf("\n");

    // Check disconnected vertices
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i]) {
            printf("Note: The graph is disconnected. Vertex %d was not reached.\n", i);
        }
    }
}

// ------------- INPUT GRAPH -------------
void input_graph(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int* num_vertices, int graph_type) {
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

    printf("Enter edges (src dest), vertices from 0 to %d:\n", *num_vertices - 1);

    for (i = 0; i < num_edges; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);

        if (src < 0 || src >= *num_vertices || dest < 0 || dest >= *num_vertices) {
            printf("Invalid vertex index. Skipping.\n");
            continue;
        }

        adj_matrix[src][dest] = 1;
        add_edge_to_list(src, dest);

        // Undirected graph — add reverse edge
        if (graph_type == 0) {
            adj_matrix[dest][src] = 1;
            add_edge_to_list(dest, src);
        }
    }
}

// ------------- DISPLAY MATRIX -------------
void display_matrix(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int n) {
    printf("\n==================================\n");
    printf("        A D J A C E N C Y   M A T R I X\n");
    printf("==================================\n");

    printf("  | ");
    for (int i = 0; i < n; i++) printf("%d ", i);

    printf("\n--+");
    for (int i = 0; i < n; i++) printf("--");
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d | ", i);
        for (int j = 0; j < n; j++)
            printf("%d ", adj_matrix[i][j]);
        printf("\n");
    }
}

// ------------- DISPLAY LIST -------------
void display_list(int n) {
    printf("\n==============================\n");
    printf("        A D J A C E N C Y   L I S T\n");
    printf("==============================\n");

    for (int i = 0; i < n; i++) {
        printf("Vertex %d:", i);

        Node* temp = adj_list[i];
        while (temp != NULL) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// ------------- MAIN -------------
int main() {
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices = 0;
    int choice, start_node;

    printf("Select Graph Type:\n");
    printf("0. Undirected Graph (Default)\n");
    printf("1. Directed Graph\n");
    printf("Enter choice (0 or 1): ");
    scanf("%d", &choice);

    int graph_type = (choice == 1) ? 1 : 0;

    printf("\n--- Inputting %s Graph ---\n", (graph_type == 0) ? "Undirected" : "Directed");

    input_graph(adj_matrix, &num_vertices, graph_type);

    display_matrix(adj_matrix, num_vertices);
    display_list(num_vertices);

    // DFS
    printf("\n--- Running Depth-First Search ---\n");
    printf("Enter starting vertex for DFS (0 to %d): ", num_vertices - 1);
    scanf("%d", &start_node);

    if (start_node >= 0 && start_node < num_vertices)
        dfs(start_node, num_vertices);
    else
        printf("Invalid starting vertex. Skipping DFS.\n");

    // Free adjacency list memory
    for (int i = 0; i < num_vertices; i++) {
        Node* curr = adj_list[i];
        Node* next;
        while (curr != NULL) {
            next = curr->next;
            free(curr);
            curr = next;
        }
    }

    return 0;
}
