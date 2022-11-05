#ifndef NODE_H
#define NODE_H
#include <global.h>

typedef struct node_list nd_list;
typedef struct node nd;

// 1. Node strcuture
typedef struct node {
    int data_type;
    int node_id;
    void* data;

    nd_list* head_list;
} nd;

// 2. Node list structure
typedef struct node_list{
    nd* node_data;
    nd_list* next_node;
} nd_list;

// 3. All nodes in graph
nd_list all_nodes = {NULL, NULL};

// 4. Functions
nd_list* create_list_node();
nd* create_node();

#endif