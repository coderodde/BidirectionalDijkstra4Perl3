#ifndef COM_GITHUB_CODERODDE_BIDIR_SEARCH_GRAPH_VERTEX_MAP_H
#define	COM_GITHUB_CODERODDE_BIDIR_SEARCH_GRAPH_VERTEX_MAP_H

#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph_vertex_map_entry {
    size_t                         vertex_id;
    struct GraphVertex*            vertex;
    struct graph_vertex_map_entry* chain_next;
    struct graph_vertex_map_entry* prev;
    struct graph_vertex_map_entry* next;
} graph_vertex_map_entry;

typedef struct graph_vertex_map {
    graph_vertex_map_entry** table;
    graph_vertex_map_entry* head;
    graph_vertex_map_entry* tail;
    size_t                   table_capacity;
    size_t                   size;
    size_t                   max_allowed_size;
    size_t                   mask;
    float                    load_factor;
} graph_vertex_map;

typedef struct graph_vertex_map_iterator {
    graph_vertex_map*       map;
    graph_vertex_map_entry* next_entry;
    size_t                  iterated_count;
} graph_vertex_map_iterator;


/***************************************************************************
* Allocates a new, empty map with given hash function and given equality   *
* testing function.                                                        *
***************************************************************************/
graph_vertex_map* graph_vertex_map_alloc(
        size_t initial_capacity,
        float load_factor);

/***************************************************************************
* If p_map does not contain the key p_key, inserts it in the map,          *
* associates value with it and return NULL. Otherwise updates the value    *
* and returns the old value.                                               *
***************************************************************************/
int graph_vertex_map_put(graph_vertex_map* map,
                         size_t vertex_id,
                         struct GraphVertex* vertex);

/***************************************************************************
* Returns a positive value if p_key is mapped to some value in this map.   *
***************************************************************************/
int graph_vertex_map_contains_key(graph_vertex_map* map, size_t vertex_id);

/***************************************************************************
* Returns the value associated with the p_key, or NULL if p_key is not     *
* mapped in the map.                                                       *
***************************************************************************/
struct GraphVertex* graph_vertex_map_get(graph_vertex_map * map,
                                         size_t vertex_id);

void graph_vertex_map_remove(graph_vertex_map* map, size_t vertex_id);

/*************************************************************************
Clears entirely the distance map.
*************************************************************************/
void graph_vertex_map_free(graph_vertex_map* map);

graph_vertex_map_iterator* graph_vertex_map_iterator_alloc
        (graph_vertex_map* map);

/***************************************************************************
* Returns the number of keys not yet iterated over.                        *
***************************************************************************/
int graph_vertex_map_iterator_has_next
        (graph_vertex_map_iterator* iterator);

/***************************************************************************
* Loads the next entry in the iteration order.                             *
***************************************************************************/
int unordered_map_iterator_next(
        graph_vertex_map_iterator* iterator,
        size_t* key_pointer,
        struct GraphVertex** value_pointer);

/***************************************************************************
* Deallocates the map iterator.                                            *
***************************************************************************/
void graph_vertex_map_iterator_free(
        graph_vertex_map_iterator* iterator);

#endif	/* COM_GITHUB_CODERODDE_BIDIR_SEARCH_DISTANCE_MAP_H */