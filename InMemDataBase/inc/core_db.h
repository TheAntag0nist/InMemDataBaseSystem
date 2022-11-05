#ifndef CORE_DB_H
#define CORE_DB_H
#include <global.h>
#include <log.h>

typedef struct database_context{
    int db_shm_id;
    int db_sem_id;

    char* db_name;
    void* mem_ptr;
} db_context;

db_context create_db_context(char* db_name, int db_uid);
int core_save_db(db_context* db_context, char* save_path);
int core_create_db_shm(char* db_name, int db_uid);
int core_resize_db_shm(db_context* db_context);
int core_destroy_db(db_context* db_context);
int core_attach_db(db_context* db_context);
int core_detach_db(db_context* db_context);

int core_write_db(db_context* db_context, char* data);
int core_read_db(db_context* db_context, char* data);

#endif