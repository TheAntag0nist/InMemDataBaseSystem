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
    init_nd->node_id = node_counter;
    init_nd->data_type = 0;
    init_nd->data = NULL;
    ++node_counter;
    // 3. Return node
    return init_nd;
}

int display_node(nd* node){
    // 1. Allocate memory
    char* global_str = malloc(node->data_sz + 512);
    char* data_str = malloc(node->data_sz + 1);
    char temp[128];
    char* ptr;
    // 2. Configure string
    for(int i = 0; i < node->data_sz; ++i)
        data_str[i] = ((char*)node->data)[i];
    data_str[node->data_sz] = '\0';
    // 3. Write data to global string
    strcpy(global_str, "ID: ");
    strcat(global_str, "\n");

    strcpy(global_str, "DATA: ");
    strcat(global_str, data_str);
    strcat(global_str, "\n");

    strcpy(global_str, "TYPE: ");
    strcat(global_str, "\n");
    // 4. Display string
    info(global_str);
    // 5. Return result
    free(global_str);
    free(data_str);
    return SUCCESS;   
}

char* serialize_node(nd* node){
    int node_sz = node->data_sz + 3 * sizeof(int);
    char* buf = malloc(node_sz);

    memcpy(buf, &(node->data_type), 4);
    memcpy(buf, &(node->node_id), 4);
    memcpy(buf, &(node->data_sz), 4);
    memcpy(buf, (node->data), 4);

    return buf;
}