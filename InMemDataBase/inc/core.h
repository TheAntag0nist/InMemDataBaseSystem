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
int disconnect_db(db_context* context);
int connect_db(db_context* db_context, char* db_name, int db_uid);

// Data Base Table functions
int create_table();
int delete_table();

// Data Base Parse Functions
int search_node(db_context* context, int id, nd* node);
int search_edge(db_context* context, int id, edge* edge);
int delete(int id);

int add_node(db_context*  db_context, nd* node);
int add_edge(db_context*  db_context, edge* edge);

int get_database_system_info(db_context* context, db_sys_info* sys_info);
#endif