/**
 * @file graph_adj_list.c
 * @brief Stub implementation for a Graph represented using Adjacency Lists.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "graph_adj_list.h" // Assuming graph_adj_list.h is in the same directory or include path is set
#include <stdio.h>          // For printf
#include <stdlib.h>         // For NULL
// #include <stdbool.h> // bool is already included via graph_adj_list.h

GraphAdjList* graph_adj_list_create(int num_vertices) {
    printf("STUB: graph_adj_list_create not implemented\n");
    (void)num_vertices; // Parameter unused in stub
    return NULL;
}

void graph_adj_list_destroy(GraphAdjList* graph) {
    printf("STUB: graph_adj_list_destroy not implemented\n");
    (void)graph; // Parameter unused in stub
}

bool graph_adj_list_add_edge(GraphAdjList* graph, int src_vertex_id, int dest_vertex_id) {
    printf("STUB: graph_adj_list_add_edge not implemented\n");
    (void)graph;           // Parameter unused in stub
    (void)src_vertex_id;   // Parameter unused in stub
    (void)dest_vertex_id;  // Parameter unused in stub
    return false; // Default to false, indicating error or no change for a stub
}

bool graph_adj_list_remove_edge(GraphAdjList* graph, int src_vertex_id, int dest_vertex_id) {
    printf("STUB: graph_adj_list_remove_edge not implemented\n");
    (void)graph;
    (void)src_vertex_id;
    (void)dest_vertex_id;
    return false;
}

bool graph_adj_list_has_edge(const GraphAdjList* graph, int src_vertex_id, int dest_vertex_id) {
    printf("STUB: graph_adj_list_has_edge not implemented\n");
    (void)graph;
    (void)src_vertex_id;
    (void)dest_vertex_id;
    return false;
}

int graph_adj_list_get_num_vertices(const GraphAdjList* graph) {
    printf("STUB: graph_adj_list_get_num_vertices not implemented\n");
    (void)graph;
    return 0; // Default for an uninitialized or empty graph stub
}

void graph_adj_list_print(const GraphAdjList* graph) {
    printf("STUB: graph_adj_list_print not implemented\n");
    (void)graph;
}

void graph_adj_list_bfs(const GraphAdjList* graph, int start_vertex_id,
                        void (*visitor)(int vertex_id, void* user_data), void* user_data) {
    printf("STUB: graph_adj_list_bfs not implemented\n");
    (void)graph;
    (void)start_vertex_id;
    (void)visitor;
    (void)user_data;
}

void graph_adj_list_dfs(const GraphAdjList* graph, int start_vertex_id,
                        void (*visitor)(int vertex_id, void* user_data), void* user_data) {
    printf("STUB: graph_adj_list_dfs not implemented\n");
    (void)graph;
    (void)start_vertex_id;
    (void)visitor;
    (void)user_data;
}