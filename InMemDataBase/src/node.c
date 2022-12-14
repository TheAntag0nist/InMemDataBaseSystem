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
    init_nd->data_type = ND_TYPE_DEFAULT;
    init_nd->data = NULL;
    ++node_counter;
    // 3. Return node
    return init_nd;
}

int display_node(nd* node){
    // 1. Allocate memory
    char* global_str = malloc(node->data_sz + 512);
    char temp[128];
    char* ptr;
    // 3. Write data to global string
    strcpy(global_str, "\nID: ");
    itoa(node->node_id, temp);
    strcat(global_str, temp);
    strcat(global_str, "\n");

    strcat(global_str, "DATA: ");
    strcat(global_str, node->data);
    strcat(global_str, "\n");

    strcat(global_str, "TYPE: ");
    itoa(node->data_type, temp);
    strcat(global_str, temp);
    strcat(global_str, "\n");
    // 4. Display string
    info(global_str);
    // 5. Return result
    free(global_str);
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


void itoa(int n, char s[]){
    int i, sign;
 
    if ((sign = n) < 0)  /* записываем знак */
        n = -n;          /* делаем n положительным числом */
    i = 0;
    do {       /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0';   /* берем следующую цифру */
    } while ((n /= 10) > 0);     /* удаляем */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

 /* reverse:  переворачиваем строку s на месте */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
