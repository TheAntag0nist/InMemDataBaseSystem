#ifndef NODE_H
#define NODE_H
#include <global.h>
#include <log.h>

typedef struct node_list nd_list;
typedef struct node nd;

int node_counter = 0;

typedef struct pair{
    int second;
    int first;
} pair;

// 1. Node strcuture
typedef struct node {
    int data_type;
    int node_id;
    
    void* data;
    int data_sz;
} nd;

// 2. Universal node list structure
typedef struct node_list{
    nd_list* next_node;
    void* node_data;
} nd_list;

// 3. All nodes in graph
nd_list all_nodes = {NULL, NULL};
// 4. Edges in graph
nd_list edges = {NULL, NULL};

// 5. Functions
nd_list* create_list_node();
int delete_node(nd* node);
nd* create_node();

int display_node(nd* node);
char* serialize_node(nd* node);

#endif