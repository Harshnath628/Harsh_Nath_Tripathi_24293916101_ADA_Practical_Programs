#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj_list[MAX_VERTICES] = {NULL};

Node* create_node(int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
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

void input_graph(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int *num_vertices, int graph_type) {
    int i, j, num_edges, src, dest;

    printf("Enter the number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", num_vertices);

    for (i = 0; i < *num_vertices; i++)
        for (j = 0; j < *num_vertices; j++)
            adj_matrix[i][j] = 0;

    printf("Enter the number of edges: ");
    scanf("%d", &num_edges);

    printf("Enter edges (source destination):\n");
    for (i = 0; i < num_edges; i++) {
        scanf("%d %d", &src, &dest);
        adj_matrix[src][dest] = 1;
        add_edge_to_list(src, dest);

        if (graph_type == 0) { // Undirected
            adj_matrix[dest][src] = 1;
            add_edge_to_list(dest, src);
        }
    }
}

void display_matrix(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int n) {
    printf("\nADJACENCY MATRIX\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", adj_matrix[i][j]);
        printf("\n");
    }
}

void display_list(int n) {
    printf("\nADJACENCY LIST\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d:", i);
        Node* current = adj_list[i];
        while (current != NULL) {
            printf(" -> %d", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
    int choice;

    printf("Select Graph Type:\n0. Undirected\n1. Directed\nChoice: ");
    scanf("%d", &choice);

    input_graph(adj_matrix, &num_vertices, choice);
    display_matrix(adj_matrix, num_vertices);
    display_list(num_vertices);

    return 0;
}
