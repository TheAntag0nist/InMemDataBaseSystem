#include <node.h>

nd_list* create_list_node(){
    // 1. Node data
    nd_list* init_list_nd = malloc(sizeof(nd_list));
    // 2. Write data
    init_list_nd->node_data = NULL;
    init_list_nd->next_node = NULL;
    // 3. Return list node
    return init_list_nd;
}

nd* create_node(){
    // 1. Node data
    nd* init_nd = malloc(sizeof(nd));
    // 2. Write data
    init_nd->head_list = NULL;
    init_nd->data_type = 0;
    init_nd->data = NULL;
    // 3. Return node
    return init_nd;
}