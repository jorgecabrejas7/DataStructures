/**
 * @file graph_adj_matrix.c
 * @brief Stub implementation for a Graph represented using an Adjacency Matrix.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "graph_adj_matrix.h" // Assuming graph_adj_matrix.h is in the same directory or include path is set
#include <stdio.h>            // For printf
#include <stdlib.h>           // For NULL
// #include <stdbool.h> // bool is already included via graph_adj_matrix.h

GraphAdjMatrix* graph_adj_matrix_create(int num_vertices) {
    printf("STUB: graph_adj_matrix_create not implemented\n");
    (void)num_vertices; // Parameter unused in stub
    return NULL;
}

void graph_adj_matrix_destroy(GraphAdjMatrix* graph) {
    printf("STUB: graph_adj_matrix_destroy not implemented\n");
    (void)graph; // Parameter unused in stub
}

// Corrected parameters to match .h (v1_id, v2_id)
bool graph_adj_matrix_add_edge(GraphAdjMatrix* graph, int v1_id, int v2_id) {
    printf("STUB: graph_adj_matrix_add_edge not implemented\n");
    (void)graph;  // Parameter unused in stub
    (void)v1_id;  // Parameter unused in stub
    (void)v2_id;  // Parameter unused in stub
    return false; // Default to false, indicating error or no change for a stub
                  // .h says: "true if the edge was successfully added (or already existed)"
                  // For a stub, false is safer to indicate it didn't actually do the work.
}

// Corrected parameters to match .h (v1_id, v2_id)
bool graph_adj_matrix_remove_edge(GraphAdjMatrix* graph, int v1_id, int v2_id) {
    printf("STUB: graph_adj_matrix_remove_edge not implemented\n");
    (void)graph;
    (void)v1_id;
    (void)v2_id;
    return false; // .h says: "true if the edge was 'removed' ... false if vertex IDs are out of bounds."
                  // For a stub, false is fine.
}

// Corrected parameters to match .h (v1_id, v2_id)
bool graph_adj_matrix_has_edge(const GraphAdjMatrix* graph, int v1_id, int v2_id) {
    printf("STUB: graph_adj_matrix_has_edge not implemented\n");
    (void)graph;
    (void)v1_id;
    (void)v2_id;
    return false;
}

int graph_adj_matrix_get_num_vertices(const GraphAdjMatrix* graph) {
    printf("STUB: graph_adj_matrix_get_num_vertices not implemented\n");
    (void)graph;
    return 0; // Default for an uninitialized or empty graph stub
}

void graph_adj_matrix_print(const GraphAdjMatrix* graph) {
    printf("STUB: graph_adj_matrix_print not implemented\n");
    (void)graph;
}

// Corrected visitor function signature as per .h file
void graph_adj_matrix_bfs(const GraphAdjMatrix* graph, int start_vertex_id,
                          void (*visitor)(int vertex_id, void* user_data), void* user_data) {
    printf("STUB: graph_adj_matrix_bfs not implemented\n");
    (void)graph;
    (void)start_vertex_id;
    (void)visitor;
    (void)user_data;
}

// Corrected visitor function signature as per .h file
void graph_adj_matrix_dfs(const GraphAdjMatrix* graph, int start_vertex_id,
                          void (*visitor)(int vertex_id, void* user_data), void* user_data) {
    printf("STUB: graph_adj_matrix_dfs not implemented\n");
    (void)graph;
    (void)start_vertex_id;
    (void)visitor;
    (void)user_data;
}

// Functions from your .c stub that were not in the .h file are omitted:
// - graph_adj_matrix_get_edge_weight
// - graph_adj_matrix_get_num_edges
// The create and add_edge functions in the stub also had extra parameters
// (is_directed, is_weighted, weight) which are not in the .h for this unweighted, undirected graph.