#include "stdio.h"
#include "core.h"
#include "cmd.h"

int main() {
    //int op_res = FAILURE;
    //db_context context;
    //// 1. Create database
    //op_res = create_db(&context, "students.db", 0);
    //if (op_res != SUCCESS)
    //    fatal("Can't create DB");
    //info("DB was created");
    //// 2. Load database from file
    //load_db(&context, context.db_name);
    //// 3. Write data to database
    //core_write_db(&context, "Hello, world!");
    main_loop();
    //// 4. Save database
    //save_db(&context, context.db_name);
    //// 5. Destroy database
    //op_res = destroy_db(&context);
    return 0;
}