#include <core.h>

int destroy_db(db_context* context) {
    return core_destroy_db(context);
}

int create_db(db_context* context, char* name, int uid) {
    *context = create_db_context(name, uid);
    return SUCCESS;
}

int save_db(db_context* context, char* path) {
    return SUCCESS;
}

int disconnect_db(){
    return SUCCESS;
}

int connect_db(){
    return SUCCESS;
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