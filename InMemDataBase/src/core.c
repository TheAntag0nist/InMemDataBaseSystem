#include <core.h>

int destroy_db(db_context* context) {
    return core_destroy_db(context);
}

int create_db(db_context* context, char* name, int uid) {
    *context = create_db_context(name, uid);
    return SUCCESS;
}

int save_db(db_context* context, char* path) {
    return core_save_db(context, path);
}

int load_db(db_context* context, char* path){
    return core_load_db(context, path);
}

int disconnect_db(db_context* context){
    return core_destroy_db(context);
}

int connect_db(db_context* db_context, char* db_name, int db_uid){
    return core_connect_db(db_name, db_uid, db_context);
}

int search_node(db_context* context, int id, nd* node){
    return core_read_node_db(context, id, node);
}

int search_edge(db_context* context, int id, edge* edge){
    return core_read_edge_db(context, id, edge);
}

int delete(int id){
    return SUCCESS;
}

int add_node(db_context*  db_context, nd* node){
    return core_write_node_db(db_context, node);
}

int add_edge(db_context*  db_context, edge* edge){
    return core_write_edge_db(db_context, edge);
}

int get_database_system_info(db_context* context, db_sys_info* sys_info){
    return core_read_sys_info(context, sys_info);
}