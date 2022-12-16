#ifndef CORE_DB_H
#define CORE_DB_H
#include <global.h>
#include <node.h>
#include <log.h>

// TODO: Обернуть attach и detach как транзакцию с передачей указателя на функцию

typedef struct shm_data{
    int db_shm_id;
    int db_sem_id;
    int db_size;
} shm_data;

typedef struct database_context{
    int db_shm_id;
    int db_sem_id;
    int db_size;

    char* db_name;
    void* mem_ptr;
} db_context;

typedef struct database_system_info{
    char db_magic[4];
    int db_size;
    int db_cnt_nodes;
    int db_cnt_edges;
    time_t db_last_modified;
    time_t db_created;
} db_sys_info;

int core_connect_db(char* db_name, int db_uid, db_context* db_context);
int core_resize_db_shm(db_context* db_context, int bytes_sz);
db_context create_db_context(char* db_name, int db_uid);

int core_save_db(db_context* db_context, char* save_path);
int core_load_db(db_context* db_context, char* load_path);

int core_connect_db_sem(char* db_name, int db_uid);
int core_is_exist_db_shm(char* db_name, int db_uid);

int core_create_db_sem(char* db_name, int sem_num);
int core_create_db_shm(char* db_name, int db_uid);

int core_destroy_db(db_context* db_context);

int core_attach_db(db_context* db_context);
int core_detach_db(db_context* db_context);

int core_check_magic(db_context* db_context);
int core_init_sys_info(db_context* db_context);
int core_write_sys_info(db_context* db_context, db_sys_info sys_info);
int core_read_sys_info(db_context* db_context, db_sys_info* sys_info);

int core_write_db(db_context* db_context, char* data);
int core_read_db(db_context* db_context, char* data, int ptr_start, int size);

int core_write_node_db(db_context* db_context, nd* node);
int core_write_edge_db(db_context* db_context, edge* edges);

int core_read_node_db(db_context* db_context, int id, nd* node);
int core_read_edge_db(db_context* db_context, int id, edge* edge);

int get_last_node_offset(db_context* db_context, int* offset);
#endif