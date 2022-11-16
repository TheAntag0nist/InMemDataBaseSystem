#ifndef CORE_DB_H
#define CORE_DB_H
#include <global.h>
#include <log.h>

typedef struct database_context{
    int db_shm_id;
    int db_sem_id;
    int db_size;

    char* db_name;
    void* mem_ptr;
} db_context;

int core_connect_db(char* db_name, int db_uid, db_context* db_context);
int core_resize_db_shm(db_context* db_context, int bytes_sz);
int core_save_db(db_context* db_context, char* save_path);
int core_load_db(db_context* db_context, char* load_path);
db_context create_db_context(char* db_name, int db_uid);
int core_connect_db_sem(char* db_name, int db_uid);
int core_connect_db_shm(char* db_name, int db_uid);
int core_create_db_sem(char* db_name, int sem_num);
int core_create_db_shm(char* db_name, int db_uid);
int core_destroy_db(db_context* db_context);
int core_attach_db(db_context* db_context);
int core_detach_db(db_context* db_context);

int core_write_db(db_context* db_context, char* data);
int core_read_db(db_context* db_context, char* data);

#endif