#include <core_db.h>

db_context create_db_context(char* db_name, int db_uid){
    db_context context;

    // 1. Get database shared memory id
    context.db_shm_id = core_create_db_shm(db_name, db_uid);

    // 2. Save database name
    int name_sz = strlen(db_name);
    context.db_name = (char*) malloc(name_sz);
    strncpy(context.db_name, db_name, name_sz);

    // 3. Return database context
    return context;
}

int core_create_db_shm(char* db_name, int db_uid){
    // 1. Create unique key
    key_t key = ftok(db_name, db_uid);

    // 2. Create shared memory 
    int shm_id = shmget(key, DEFAULT_DB_SIZE, IPC_CREAT | 0666);

    // 3. Check id
    if(shm_id == IPC_FAIL)
        fatal("Can't create shared memory for DB");
    info("Shared memory for DB was created"); 

    // 5. Return value
    return shm_id;
}

int core_save_db(db_context* db_context, char* save_path){
    // 1. Create file
    // 2. Write database to file
    // 3. Close file
    return SUCCESS;
}

int core_resize_db_shm(db_context* db_context){
    // 1. Unlink all processes from db
    // 2. Resize database
    // 3. Link all processes
    return SUCCESS;
}

int core_destroy_db(db_context* db_context){
    // 1. Destroying shared memory
    shmctl( db_context->db_shm_id, IPC_RMID, NULL);
    
    // 2. Destroy database name
    free(db_context->db_name);

    // 3. Display message
    info("Shared memory for DB was destroyed");

    // 3. Return result
    return SUCCESS;
}


int core_attach_db(db_context* db_context){
    if(db_context->mem_ptr == NULL){
        // 1. Attach database
        db_context->mem_ptr = shmat(db_context->db_shm_id, NULL, 0);
        // 2. Display message
        if(db_context->mem_ptr == (void*) IPC_FAIL)
            fatal("Can't attach shared memory of DB");
        info("Successfully attached shared memory of DB");
    }
    else{
        warning("Already attached to shared memory of DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_detach_db(db_context* db_context){
    if (db_context->mem_ptr != NULL) {
        // 1. Detaching shared memory
        int res = shmdt(db_context->mem_ptr);
        // 2. Display message
        if(res == IPC_FAIL)
            fatal("Can't detach shared memory");
        info("Shared memory was detached");
        // 3. Set ptr to NULL
        db_context->mem_ptr = NULL;
    }
    else{
        warning("No need to detach");
        return FAILURE;
    }
        
    return SUCCESS;
}

int write_db(db_context* db_context, char* data){
    // 1. Attach database
    core_attach_db(db_context);

    // Some actions here

    // 2. Detach database
    core_detach_db(db_context);
    return SUCCESS;
}

int read_db(db_context* db_context, char* data){
    // 1. Attach database
    core_attach_db(db_context);

    // Some actions here

    // 2. Detach database
    core_detach_db(db_context);
    return SUCCESS;
}