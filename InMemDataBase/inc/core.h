#ifndef CORE_H
#define CORE_H
#include <core_db.h>
#include <global.h>
#include <log.h>

// Data Base Context functions 
int create_db(db_context* context, char* name, int uid);
int save_db(db_context* context, char* path);
int load_db(db_context* context, char* path);
int destroy_db(db_context* context);

// Data Base Connection functions
int disconnect_db();
int connect_db();

// Data Base Table functions
int create_table();
int delete_table();

// Data Base Parse Functions
int search();
int delete();
int add();

#endif