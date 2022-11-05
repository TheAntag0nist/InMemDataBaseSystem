#include "stdio.h"
#include "core.h"

int main() {
    int op_res = FAILURE;
    db_context context;

    op_res = create_db(&context, "students.db", 0);
    if (op_res != SUCCESS)
        fatal("Can't create database");
    info("Successfully create database");

    op_res = destroy_db(&context);
    return 0;
}