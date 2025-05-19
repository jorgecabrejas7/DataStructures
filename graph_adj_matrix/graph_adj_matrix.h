/* Placeholder for graph_adj_matrix.h */
/**
 * @file graph_adj_matrix.h
 * @brief Defines the interface for a Graph represented using an Adjacency Matrix,
 *        storing integer vertex IDs. This version is for an unweighted, undirected graph.
 *
 * == Clear Definition ==
 * A Graph is a non-linear data structure consisting of a set of 'vertices' (or nodes)
 * and a set of 'edges' that connect pairs of vertices.
 *
 * This implementation uses an Adjacency Matrix representation:
 * - The graph is represented by a 2D square matrix (let's call it `matrix`) of size
 *   `num_vertices` x `num_vertices`.
 * - For an unweighted graph, `matrix[i][j] = 1` (or `true`) if there is an edge
 *   connecting vertex `i` and vertex `j`, and `matrix[i][j] = 0` (or `false`) otherwise.
 * - Since this is an undirected graph, the matrix will be symmetric, i.e.,
 *   `matrix[i][j] = matrix[j][i]`.
 * - Vertices are identified by integer IDs, typically from 0 to `num_vertices - 1`.
 *
 * == Key Properties and Characteristics ==
 * - Vertices: Identified by 'int' IDs (0 to N-1).
 * - Edges: Represent connections between pairs of vertices. Undirected and unweighted.
 * - Adjacency Matrix: A V x V matrix where V is the number of vertices.
 *   An entry (i, j) is 1 if an edge exists between vertex i and j, else 0.
 * - Dense Graphs: Adjacency matrices are more space-efficient (relative to their
 *   worst-case O(V^2)) for dense graphs where the number of edges E is close to V^2.
 *
 * == Common Operations ==
 * - Creation: Initialize a graph with a specific number of vertices and no edges
 *   (matrix initialized to all 0s).
 * - Destruction: Free all memory associated with the graph (the matrix).
 * - Add Edge: Adds an edge between two specified vertices by setting
 *   `matrix[i][j] = 1` and `matrix[j][i] = 1`.
 * - Remove Edge: Removes an edge by setting `matrix[i][j] = 0` and `matrix[j][i] = 0`.
 * - Check Edge (Has Edge): Checks if an edge exists between two vertices in O(1) time
 *   by looking up `matrix[i][j]`.
 * - Get Neighbors: To get neighbors of a vertex `i`, one must iterate through row `i`
 *   of the matrix and collect all `j` where `matrix[i][j] = 1`. This is O(V).
 * - Graph Traversal Algorithms (BFS, DFS): Can be implemented but iterating neighbors is O(V).
 *
 * == Typical Use Cases ==
 * - Dense graphs where V is relatively small, and edge existence checks are frequent.
 * - When a simple representation is favored and V^2 space is acceptable.
 * - Certain graph algorithms that benefit from matrix operations (though less common for basic traversals).
 *
 * == Advantages (Adjacency Matrix) ==
 * - Fast edge existence check: O(1) to check if an edge (u,v) exists.
 * - Fast add/remove edge: O(1).
 * - Conceptually simple for dense graphs.
 *
 * == Disadvantages (Adjacency Matrix) ==
 * - Space inefficient for sparse graphs: Always requires O(V^2) space, regardless
 *   of the number of edges.
 * - Iterating over all neighbors of a vertex takes O(V) time, even if a vertex
 *   has few neighbors. This makes algorithms like BFS/DFS slower on sparse graphs
 *   (O(V^2) total time) compared to adjacency lists (O(V+E)).
 * - Adding/removing vertices is expensive (requires resizing the entire matrix).
 *   This implementation assumes a fixed number of vertices.
 *
 * The matrix itself will be a dynamically allocated 2D array.
 */

#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For printf (and NULL)

// Forward declaration
typedef struct GraphAdjMatrix GraphAdjMatrix;

/**
 * @brief Structure representing the Graph using an Adjacency Matrix.
 *
 * @param num_vertices The total number of vertices in the graph.
 * @param matrix A pointer to an array of pointers, representing the 2D adjacency matrix.
 *               `matrix[i][j] == 1` if edge (i,j) exists, else 0.
 *               Memory for this matrix is laid out as `num_vertices` pointers,
 *               each pointing to an array of `num_vertices` integers.
 */
struct GraphAdjMatrix {
    int num_vertices;
    int** matrix; // Using int for matrix elements (0 or 1) for simplicity. Could be bool.
};

// === Function Prototypes ===

/**
 * @brief Creates a graph with a specified number of vertices and no edges.
 *
 * Initializes the V x V adjacency matrix with all zeros.
 *
 * @param num_vertices The number of vertices in the graph. Vertices will be
 *                     numbered 0 to `num_vertices - 1`. Must be non-negative.
 * @return GraphAdjMatrix* A pointer to the newly created graph, or NULL if
 *                         memory allocation fails or `num_vertices` is negative.
 * @note The caller is responsible for eventually calling graph_adj_matrix_destroy().
 */
GraphAdjMatrix* graph_adj_matrix_create(int num_vertices);

/**
 * @brief Destroys the graph, freeing the adjacency matrix and the graph structure itself.
 *
 * If `graph` is NULL, no operation is performed.
 *
 * @param graph A pointer to the GraphAdjMatrix to be destroyed. Can be NULL.
 * @post All memory associated with `graph` is freed. `graph` becomes invalid.
 */
void graph_adj_matrix_destroy(GraphAdjMatrix* graph);

/**
 * @brief Adds an undirected edge between two vertices `v1_id` and `v2_id`.
 *
 * Sets `matrix[v1_id][v2_id] = 1` and `matrix[v2_id][v1_id] = 1`.
 *
 * @param graph A pointer to the GraphAdjMatrix. Must not be NULL.
 * @param v1_id The ID of the first vertex (0 to num_vertices-1).
 * @param v2_id The ID of the second vertex (0 to num_vertices-1).
 * @return bool true if the edge was successfully added (or already existed),
 *              false if vertex IDs are out of bounds.
 * @pre `graph` must be a valid, non-NULL pointer.
 * @pre `v1_id` and `v2_id` must be valid vertex IDs.
 * @post An edge (v1_id, v2_id) exists in the graph.
 */
bool graph_adj_matrix_add_edge(GraphAdjMatrix* graph, int v1_id, int v2_id);

/**
 * @brief Removes an undirected edge between `v1_id` and `v2_id`.
 *
 * Sets `matrix[v1_id][v2_id] = 0` and `matrix[v2_id][v1_id] = 0`.
 *
 * @param graph A pointer to the GraphAdjMatrix. Must not be NULL.
 * @param v1_id The ID of the first vertex.
 * @param v2_id The ID of the second vertex.
 * @return bool true if the edge was "removed" (i.e., corresponding matrix cells set to 0).
 *              This is true even if the edge didn't exist (cells were already 0).
 *              Returns false if vertex IDs are out of bounds.
 * @pre `graph` must be a valid, non-NULL pointer.
 * @pre `v1_id` and `v2_id` must be valid vertex IDs.
 * @post The edge (v1_id, v2_id) effectively does not exist.
 */
bool graph_adj_matrix_remove_edge(GraphAdjMatrix* graph, int v1_id, int v2_id);

/**
 * @brief Checks if an undirected edge exists between `v1_id` and `v2_id`.
 *
 * Checks the value of `matrix[v1_id][v2_id]`.
 *
 * @param graph A pointer to a constant GraphAdjMatrix. Must not be NULL.
 * @param v1_id The ID of the first vertex.
 * @param v2_id The ID of the second vertex.
 * @return bool true if an edge exists (matrix cell is 1), false otherwise
 *              (cell is 0, or IDs are out of bounds).
 * @pre `graph` must be a valid, non-NULL pointer.
 * @pre `v1_id` and `v2_id` should be valid vertex IDs for a meaningful check.
 */
bool graph_adj_matrix_has_edge(const GraphAdjMatrix* graph, int v1_id, int v2_id);

/**
 * @brief Returns the number of vertices in the graph.
 *
 * @param graph A pointer to a constant GraphAdjMatrix. Must not be NULL.
 * @return int The number of vertices.
 * @pre `graph` must be a valid, non-NULL pointer.
 */
int graph_adj_matrix_get_num_vertices(const GraphAdjMatrix* graph);

/**
 * @brief (Optional helper for testing/debugging) Prints the adjacency matrix of the graph.
 *
 * @param graph A pointer to a constant GraphAdjMatrix. Can be NULL.
 */
void graph_adj_matrix_print(const GraphAdjMatrix* graph);


// --- Basic Graph Traversal Algorithm Prototypes (to be implemented using this graph representation) ---
// These will be similar to the Adjacency List versions but will iterate neighbors differently.

/**
 * @brief Performs a Breadth-First Search (BFS) starting from a given vertex.
 *
 * The `visitor` function is called for each vertex as it's visited.
 * Neighbors are found by iterating through the row of the start_vertex_id in the matrix.
 *
 * @param graph A pointer to a constant GraphAdjMatrix. Must not be NULL.
 * @param start_vertex_id The ID of the vertex from which to start the BFS.
 * @param visitor A function pointer that takes an int (the visited vertex ID) and
 *                void* user_data. It's called for each visited vertex.
 * @param user_data A pointer to user-defined data passed to the visitor.
 * @pre `graph` must be valid. `start_vertex_id` must be a valid vertex ID. `visitor` must not be NULL.
 * @note Assumes this function handles its own `visited` array.
 */
void graph_adj_matrix_bfs(const GraphAdjMatrix* graph, int start_vertex_id,
                          void (*visitor)(int vertex_id, void* user_data), void* user_data);

/**
 * @brief Performs a Depth-First Search (DFS) starting from a given vertex.
 *
 * The `visitor` function is called for each vertex as it's visited.
 * Neighbors are found by iterating through the row of the start_vertex_id in the matrix.
 *
 * @param graph A pointer to a constant GraphAdjMatrix. Must not be NULL.
 * @param start_vertex_id The ID of the vertex from which to start the DFS.
 * @param visitor A function pointer that takes an int (the visited vertex ID) and
 *                void* user_data. It's called for each visited vertex.
 * @param user_data A pointer to user-defined data passed to the visitor.
 * @pre `graph` must be valid. `start_vertex_id` must be a valid vertex ID. `visitor` must not be NULL.
 * @note Assumes this function handles its own `visited` array.
 */
void graph_adj_matrix_dfs(const GraphAdjMatrix* graph, int start_vertex_id,
                          void (*visitor)(int vertex_id, void* user_data), void* user_data);

#endif // GRAPH_ADJ_MATRIX_H