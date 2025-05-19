/**
 * @file graph_adj_list.h
 * @brief Defines the interface for a Graph represented using Adjacency Lists,
 *        storing integer vertex IDs. This version is for an unweighted, undirected graph.
 *
 * == Clear Definition ==
 * A Graph is a non-linear data structure consisting of a set of 'vertices' (or nodes)
 * and a set of 'edges' that connect pairs of vertices.
 *
 * This implementation uses an Adjacency List representation:
 * - The graph maintains an array (or list) of adjacency lists.
 * - For each vertex 'u' in the graph, there is an adjacency list `adj[u]` that
 *   stores all vertices 'v' such that there is an edge (u, v) in the graph.
 * - Since this is an undirected graph, if there's an edge (u,v), then 'v' will
 *   be in `adj[u]` and 'u' will be in `adj[v]`.
 * - The graph is unweighted, meaning edges do not have associated weights or costs.
 * - Vertices are identified by integer IDs, typically from 0 to `num_vertices - 1`.
 *
 * Each adjacency list itself will be implemented using a simple singly linked list
 * for dynamic addition of neighbors.
 *
 * == Key Properties and Characteristics ==
 * - Vertices: Identified by 'int' IDs (0 to N-1).
 * - Edges: Represent connections between pairs of vertices. Undirected and unweighted.
 * - Adjacency List: For each vertex, a list of its direct neighbors.
 * - Sparse Graphs: Adjacency lists are particularly space-efficient for graphs
 *   where the number of edges is much less than the square of the number of vertices.
 *
 * == Common Operations ==
 * - Creation: Initialize a graph with a specific number of vertices and no edges.
 * - Destruction: Free all memory associated with the graph.
 * - Add Edge: Adds an edge between two specified vertices.
 * - Remove Edge: Removes an edge between two specified vertices (more complex with lists).
 *   (For simplicity in this first pass, we might omit remove_edge or make it basic).
 * - Check Edge: Checks if an edge exists between two vertices.
 * - Get Neighbors: Retrieves the list of neighbors for a given vertex.
 * - Graph Traversal Algorithms:
 *   - Breadth-First Search (BFS): Visits neighbors level by level.
 *   - Depth-First Search (DFS): Explores as far as possible along each branch.
 *   (The algorithms themselves are separate but operate on the graph structure).
 *
 * == Typical Use Cases ==
 * - Modeling networks (social networks, computer networks, road networks).
 * - Representing relationships between entities.
 * - Pathfinding problems (e.g., shortest path - though needs weights for variants like Dijkstra).
 * - Connectivity analysis (e.g., finding connected components).
 * - Scheduling and dependency analysis (often with directed graphs).
 *
 * == Advantages (Adjacency List) ==
 * - Space efficient for sparse graphs: Space complexity is O(V + E) where V is
 *   number of vertices and E is number of edges.
 * - Efficiently iterate over neighbors of a vertex.
 * - Adding a new vertex can be done (though our fixed N vertices is simpler first).
 * - Adding an edge is efficient (O(1) if not checking for duplicates, or O(degree) if checking).
 *
 * == Disadvantages (Adjacency List) ==
 * - Checking for the existence of a specific edge (u,v) can be slower than an
 *   adjacency matrix, potentially O(degree(u)) or O(V) in worst case if lists are long.
 * - Removing an edge can also be O(degree(u)) + O(degree(v)) as you need to find
 *   the edge in two lists.
 * - Less efficient for dense graphs where E is close to V^2.
 *
 * For the linked list nodes within each adjacency list:
 */

#ifndef GRAPH_ADJ_LIST_H
#define GRAPH_ADJ_LIST_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For printf (and NULL)

// Forward declarations
typedef struct AdjListNode AdjListNode;
typedef struct GraphAdjList GraphAdjList;

/**
 * @brief Structure representing a node in an adjacency list.
 *        Stores the ID of a neighbor vertex.
 *
 * @param dest_vertex_id The integer ID of the destination (neighbor) vertex.
 * @param next A pointer to the next AdjListNode in the adjacency list for a given source vertex.
 */
struct AdjListNode {
    int dest_vertex_id;
    AdjListNode* next;
};

/**
 * @brief Structure representing the Graph using Adjacency Lists.
 *
 * @param num_vertices The total number of vertices in the graph (vertices are 0 to num_vertices-1).
 * @param adj_lists An array of pointers to AdjListNode. `adj_lists[i]` is the head
 *                  of the singly linked list of neighbors for vertex `i`.
 */
struct GraphAdjList {
    int num_vertices;
    AdjListNode** adj_lists; // Array of head pointers for adjacency lists
};

// === Function Prototypes ===

/**
 * @brief Creates a graph with a specified number of vertices and no edges.
 *
 * Initializes an adjacency list for each vertex (all initially empty).
 *
 * @param num_vertices The number of vertices in the graph. Vertices will be
 *                     numbered 0 to `num_vertices - 1`. Must be non-negative.
 * @return GraphAdjList* A pointer to the newly created graph, or NULL if
 *                       memory allocation fails or `num_vertices` is negative.
 * @note The caller is responsible for eventually calling graph_adj_list_destroy().
 */
GraphAdjList* graph_adj_list_create(int num_vertices);

/**
 * @brief Destroys the graph, freeing all adjacency lists, their nodes, and the graph structure itself.
 *
 * If `graph` is NULL, no operation is performed.
 *
 * @param graph A pointer to the GraphAdjList to be destroyed. Can be NULL.
 * @post All memory associated with `graph` is freed. `graph` becomes invalid.
 */
void graph_adj_list_destroy(GraphAdjList* graph);

/**
 * @brief Adds an undirected edge between two vertices `src_vertex_id` and `dest_vertex_id`.
 *
 * Adds `dest_vertex_id` to the adjacency list of `src_vertex_id`, AND
 * adds `src_vertex_id` to the adjacency list of `dest_vertex_id`.
 * This function should prevent adding duplicate edges if an edge already exists,
 * or define behavior if duplicates are allowed (for this spec, prevent duplicates).
 *
 * @param graph A pointer to the GraphAdjList. Must not be NULL.
 * @param src_vertex_id The ID of the source vertex (0 to num_vertices-1).
 * @param dest_vertex_id The ID of the destination vertex (0 to num_vertices-1).
 * @return bool true if the edge was successfully added (or already existed without error),
 *              false if vertex IDs are out of bounds, or memory allocation failed.
 *              If edge already exists, it can return true (no change) or false (already present).
 *              Let's define: returns true if edge is now present (newly added or pre-existing).
 *                            returns false on error (out of bounds, memory fail).
 * @pre `graph` must be a valid, non-NULL pointer.
 * @pre `src_vertex_id` and `dest_vertex_id` must be valid vertex IDs.
 * @post An edge (src_vertex_id, dest_vertex_id) exists in the graph.
 */
bool graph_adj_list_add_edge(GraphAdjList* graph, int src_vertex_id, int dest_vertex_id);

/**
 * @brief Removes an undirected edge between `src_vertex_id` and `dest_vertex_id`.
 *
 * Removes `dest_vertex_id` from `src_vertex_id`'s list and `src_vertex_id` from `dest_vertex_id`'s list.
 * (This operation can be moderately complex to implement efficiently and correctly).
 *
 * @param graph A pointer to the GraphAdjList. Must not be NULL.
 * @param src_vertex_id The ID of the source vertex.
 * @param dest_vertex_id The ID of the destination vertex.
 * @return bool true if the edge existed and was successfully removed,
 *              false if the edge did not exist or if vertex IDs are out of bounds.
 * @pre `graph` must be a valid, non-NULL pointer.
 * @pre `src_vertex_id` and `dest_vertex_id` must be valid vertex IDs.
 * @post The edge (src_vertex_id, dest_vertex_id) no longer exists.
 */
bool graph_adj_list_remove_edge(GraphAdjList* graph, int src_vertex_id, int dest_vertex_id);

/**
 * @brief Checks if an undirected edge exists between `src_vertex_id` and `dest_vertex_id`.
 *
 * Searches `src_vertex_id`'s adjacency list for `dest_vertex_id`.
 * (Since it's undirected, searching only one list is sufficient if edges are added symmetrically).
 *
 * @param graph A pointer to a constant GraphAdjList. Must not be NULL.
 * @param src_vertex_id The ID of the source vertex.
 * @param dest_vertex_id The ID of the destination vertex.
 * @return bool true if an edge exists between the two vertices, false otherwise
 *              (including if vertex IDs are out of bounds).
 * @pre `graph` must be a valid, non-NULL pointer.
 * @pre `src_vertex_id` and `dest_vertex_id` must be valid vertex IDs for a meaningful check.
 */
bool graph_adj_list_has_edge(const GraphAdjList* graph, int src_vertex_id, int dest_vertex_id);

/**
 * @brief Returns the number of vertices in the graph.
 *
 * @param graph A pointer to a constant GraphAdjList. Must not be NULL.
 * @return int The number of vertices.
 * @pre `graph` must be a valid, non-NULL pointer.
 */
int graph_adj_list_get_num_vertices(const GraphAdjList* graph);

/**
 * @brief (Optional helper for testing/debugging) Prints the adjacency lists of the graph.
 *
 * For each vertex, prints its ID followed by the IDs of its neighbors.
 *
 * @param graph A pointer to a constant GraphAdjList. Can be NULL.
 */
void graph_adj_list_print(const GraphAdjList* graph);


// --- Basic Graph Traversal Algorithm Prototypes (to be implemented using the graph) ---
// These are often separate from the DS definition but rely on it.
// For your course, you might implement these in graph_adj_list.c or in test.c.

/**
 * @brief Performs a Breadth-First Search (BFS) starting from a given vertex.
 *
 * The `visitor` function is called for each vertex as it's visited.
 * Uses a queue (which you've already defined!) internally.
 *
 * @param graph A pointer to a constant GraphAdjList. Must not be NULL.
 * @param start_vertex_id The ID of the vertex from which to start the BFS.
 * @param visitor A function pointer that takes an int (the visited vertex ID) and
 *                void* user_data. It's called for each visited vertex.
 * @param user_data A pointer to user-defined data passed to the visitor.
 * @pre `graph` must be valid. `start_vertex_id` must be a valid vertex ID. `visitor` must not be NULL.
 * @note This BFS will only traverse the connected component containing `start_vertex_id`.
 *       To visit all components, BFS may need to be called multiple times on unvisited vertices.
 *       Assumes an array `visited[num_vertices]` is managed by the caller or internally.
 *       For simplicity of this interface, we'll assume this function handles its own `visited` array.
 */
void graph_adj_list_bfs(const GraphAdjList* graph, int start_vertex_id,
                        void (*visitor)(int vertex_id, void* user_data), void* user_data);

/**
 * @brief Performs a Depth-First Search (DFS) starting from a given vertex.
 *
 * The `visitor` function is called for each vertex as it's visited.
 * Can be implemented recursively or iteratively using a stack.
 *
 * @param graph A pointer to a constant GraphAdjList. Must not be NULL.
 * @param start_vertex_id The ID of the vertex from which to start the DFS.
 * @param visitor A function pointer that takes an int (the visited vertex ID) and
 *                void* user_data. It's called for each visited vertex.
 * @param user_data A pointer to user-defined data passed to the visitor.
 * @pre `graph` must be valid. `start_vertex_id` must be a valid vertex ID. `visitor` must not be NULL.
 * @note Similar to BFS, this DFS will only traverse the connected component.
 *       Assumes an array `visited[num_vertices]` is managed by the caller or internally.
 *       For simplicity of this interface, we'll assume this function handles its own `visited` array.
 */
void graph_adj_list_dfs(const GraphAdjList* graph, int start_vertex_id,
                        void (*visitor)(int vertex_id, void* user_data), void* user_data);


#endif // GRAPH_ADJ_LIST_H