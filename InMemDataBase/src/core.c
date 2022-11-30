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

int search(){
    return SUCCESS;
}

int delete(){
    return SUCCESS;
}

int add(){
    return SUCCESS;
}