#ifndef NODE_H
#define NODE_H
#include <global.h>
#include <log.h>

typedef struct node_list nd_list;
typedef struct node nd;

extern int node_counter;

typedef struct pair{
    int second;
    int first;
} pair;

typedef pair edge;

// 1. Node strcuture
typedef struct node {
    int data_type;
    int node_id;
    
    int data_sz;
    void* data;
} nd;

// 2. Universal node list structure
typedef struct node_list{
    nd_list* next_node;
    void* node_data;
} nd_list;

// 3. All nodes in graph
static nd_list all_nodes = {NULL, NULL};
// 4. Edges in graph
static nd_list edges = {NULL, NULL};

// 5. Functions
nd_list* create_list_node();

nd* create_node();
int delete_node(nd* node);

int display_node(nd* node);
char* serialize_node(nd* node);

void itoa(int n, char s[]);
void reverse(char s[]);

#endif