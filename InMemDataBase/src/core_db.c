#include <core_db.h>

db_context create_db_context(char* db_name, int db_uid){
    db_context context;

    // 1. Get database shared memory id
    context.db_shm_id = core_create_db_shm(db_name, db_uid);

    // 2. Get database semaphore id
    // TODO: include Semaphore Core from another project
    // context.db_sem_id = core_create_db_sem(db_name, 1);

    // 3. Save size    
    context.db_size = DEFAULT_DB_SIZE;

    // 4. Set mem pointer to memory
    context.mem_ptr = NULL;

    // 5. Save database name
    int name_sz = strlen(db_name);
    context.db_name = (char*) malloc(name_sz + 1);
    strncpy(context.db_name, db_name, name_sz);
    context.db_name[name_sz] = '\0';

    core_init_sys_info(&context);
    // 6. Return database context
    return context;
}

int core_connect_db(char* db_name, int db_uid, db_context* db_context){
    key_t key = ftok(db_name, db_uid);
    printf("KEY: %d\n", key);

    int shm_id = shmget(key, 0, 0666);
    if(shm_id == IPC_FAIL){
        error("DATABASE not exist");
        return FAILURE;
    }

    // 4. Set mem pointer to memory
    db_context->mem_ptr = NULL;
    db_context->db_shm_id = shm_id;

    // 5. Save database name
    int name_sz = strlen(db_name);
    db_context->db_name = (char*) malloc(name_sz + 1);
    strncpy(db_context->db_name, db_name, name_sz);
    db_context->db_name[name_sz] = '\0';
    return SUCCESS;
}

int core_connect_db_sem(char* db_name, int db_uid){
    // TODO: include Semaphore Core from another project
}

int core_is_exist_db_shm(char* db_name, int db_uid){
    // 1. Create unique key
    key_t key = ftok(db_name, db_uid);

    info("Is database already exist?");
    
    int shm_id = shmget(key, DEFAULT_DB_SIZE, 0666);

    if(shm_id == IPC_FAIL){
        info("YES");
        return true;
    }
    else{
        info("NO");
        return false;
    }
}

int core_create_db_shm(char* db_name, int db_uid){
    // 1. Create unique key
    key_t key = ftok(db_name, db_uid);
    printf("KEY: %d\n", key);

    // 2. Create shared memory 
    int shm_id = shmget(key, DEFAULT_DB_SIZE, IPC_CREAT | 0666);

    // 3. Check id
    if(shm_id == IPC_FAIL)
        fatal("Can't create SHM for DB");
    info("SHM for DB was created/connected"); 

    // 4. Return value
    return shm_id;
}

int core_create_db_sem(char* db_name, int sem_num) {
    // 1. Modification sem
    char* modif = "_sem";
    int modif_sz = strlen(modif);

    // 2. Modify db_name
    int name_sz = strlen(db_name);
    char* path = malloc(name_sz + modif_sz + 1);

    // 3. Modification path
    strncpy(path, db_name, name_sz);
    strncat(path, modif, modif_sz);

    // 4. Create unique key
    key_t key = ftok(path, sem_num);
    int sem_id = semget(key, sem_num, IPC_CREAT | 0666);

    // 5. Check id
    if(sem_id == IPC_FAIL)
        fatal("Can't create SEM for DB");
    info("SEM for DB was created");

    // 6. Return id
    free(path);
    return sem_id;
}

// [WARN]: Just save shared memory to file 
int core_save_db(db_context* db_context, char* save_path){
    // 0. Save shared memory id
    int shm_id = db_context->db_shm_id;

    // 1. Create file
    printf("FILE_PATH: %s\n", save_path);
    FILE* file = fopen(save_path, "wb");
    int result = SUCCESS;

    // 2. Check file
    if (file == NULL){
        error("Can't create FL for save DB");
        return FAILURE;
    }

    // 3. Begin transaction
    if(core_attach_db(db_context) == SUCCESS) {
        // 4. Write database to file
        info("Save DB to FL");
        int wr_blocks = fwrite(db_context->mem_ptr, db_context->db_size, 1, file);
        if(wr_blocks != SUCCESS){
            error("Can't write DB to FL");
            core_detach_db(db_context);
            return FAILURE;
        }

        // 5. End transaction
        core_detach_db(db_context);
        info("DB was saved to FL");
    }
    else{
        error("Not save DB to FL");
        result = FAILURE;
    }

    // 6. Close file
    fclose(file);
    return result;
}

// TODO: Implement after main logic of NODES DATABASE CORE
int core_load_db(db_context* db_context, char* load_path){
    // 1. Open file
    FILE* file = fopen(load_path, "rb");
    
    // 2. Check file
    if (file == NULL){
        error("Can't open FL");
        return FAILURE;
    }

    // 3. Get file size
    // 4. Read file 
    // 5. Resize database if need
    // 6. Write data to database
    // 7. Close file
    fclose(file);
    return SUCCESS;
}

// TODO: Think about implementation of this function
int core_resize_db_shm(db_context* db_context, int bytes_sz){
    // 0. Save shared memory id
    int shm_id = db_context->db_shm_id;
    // 1. Unlink all processes from db
    // 2. Resize database (shared memory)
    // 3. Link all processes
    return SUCCESS;
}

int core_destroy_db(db_context* db_context){
    // 0. Detach memory
    if(db_context->mem_ptr != NULL) 
        core_detach_db(db_context);

    // 1. Destroying shared memory
    shmctl( db_context->db_shm_id, IPC_RMID, NULL);

    // 2. Destroy database name
    free(db_context->db_name);

    // 3. Display message
    info("DB was destroyed");

    // 4. Return result
    return SUCCESS;
}


int core_attach_db(db_context* db_context){
    if(db_context->mem_ptr != NULL)
        return SUCCESS;

    if(db_context->mem_ptr == NULL){
        // 1. Attach database
        db_context->mem_ptr = shmat(db_context->db_shm_id, NULL, 0);
        // 2. Display message
        if(db_context->mem_ptr == (void*) IPC_FAIL)
            fatal("Can't attach shared memory of DB");
        info("[+] SHM was attached");
    }
    else{
        // 3. On error
        warning("Already attached to SHM of DB");
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
            fatal("Can't detach SHM");
        info("[-] SHM was detached");
        // 3. Set ptr to NULL
        db_context->mem_ptr = NULL;
    }
    else{
        // 4. On error
        warning("No need to detach");
        return FAILURE;
    }
        
    return SUCCESS;
}

int core_write_db(db_context* db_context, char* data){
    // 1. Attach database
    if (core_attach_db(db_context) == SUCCESS) {
        // 2. Get data
        int mem_sz = db_context->db_size;
        char* ptr = db_context->mem_ptr;
        int data_sz = strlen(data);

        // 3. Copy data to memory
        info("Write data to DB");
        if(data_sz < mem_sz)
            memcpy(ptr, data, data_sz);
        else
            memcpy(ptr, data, mem_sz);
    }
    else {
        error("Can't write to DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_check_magic(db_context* db_context){
    if(db_context == NULL) 
        return FAILURE;
    
    if(core_attach_db(db_context) == SUCCESS){
        char data[4];
        core_read_db(db_context, data, 0, 4);

        info("Trying to read MAGIC from DB");

        if(data[0] == MAGIC_CH_1 &&
         data[1] == MAGIC_CH_2 &&
         data[2] == MAGIC_CH_3){
            info("MAGIC was found in DB");
            return SUCCESS;
         }
        else{
            warning("MAGIC not found in DB");
            return FAILURE;
        }
    }
    else{
        error("Can't write NODE to DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_init_sys_info(db_context* db_context){
    if(db_context == NULL) 
        return FAILURE;
    
    if(core_attach_db(db_context) == SUCCESS){
        if(core_check_magic(db_context)){
            warning("SYSTEM_INFO was already initialized");
            return SUCCESS;
        }
        
        char* ptr = db_context->mem_ptr;
        time_t curr_tm = time(0);
        db_sys_info sys_info = { "kra", DEFAULT_DB_SIZE, 0, 0, curr_tm, curr_tm};
        memcpy(ptr, (char*) &sys_info, sizeof(db_sys_info));
        info("SYSTEM_INFO was initialized");
    }
    else{
        error("Can't write NODE to DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_write_sys_info(db_context* db_context, db_sys_info sys_info){
    if(db_context == NULL) 
        return FAILURE;
    
    if(core_attach_db(db_context) == SUCCESS){
        char* ptr = db_context->mem_ptr;
        memcpy(ptr, &sys_info, sizeof(db_sys_info));
        info("SYSTEM_INFO was updated successfully");
    }
    else{
        error("Can't write NODE to DB");
        return FAILURE;
    }

    return SUCCESS;
}


int core_read_sys_info(db_context* db_context, db_sys_info* sys_info){
    if(sys_info == NULL) 
        return FAILURE;
    if(db_context == NULL) 
        return FAILURE;
    
    if(core_attach_db(db_context) == SUCCESS){
        core_read_db(db_context, (char*) sys_info, 0, sizeof(db_sys_info));
    }
    else{
        error("Can't write NODE to DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_write_node_db(db_context* db_context, nd* node){
    if(core_attach_db(db_context) == SUCCESS){
        db_sys_info sys_info = {};
        core_read_sys_info(db_context, &sys_info);

        char* ptr = db_context->mem_ptr;
        ptr += NODES_OFFSET;

        nd temp_node = {};
        for(int i = 0; i < sys_info.db_cnt_nodes; ++i) {
            core_read_node_db(db_context, i, &temp_node);
            ptr += sizeof(int) * 3 + temp_node.data_sz;
        }

        // 3. Copy data to memory
        info("Write data to DB");
        memcpy(ptr, &node->node_id, sizeof(int));
        ptr += sizeof(int);
        memcpy(ptr, &node->data_type, sizeof(int));
        ptr += sizeof(int);
        memcpy(ptr, &node->data_sz, sizeof(int));
        ptr += sizeof(int);
        memcpy(ptr, node->data, node->data_sz);

        ++sys_info.db_cnt_nodes;
        sys_info.db_last_modified = time(0);
        core_write_sys_info(db_context, sys_info);
    }
    else{
        error("Can't write NODE to DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_write_edge_db(db_context* db_context, edge* edges){
    if(core_attach_db(db_context) == SUCCESS){
        db_sys_info sys_info = {};
        core_read_sys_info(db_context, &sys_info);

        char* ptr = db_context->mem_ptr;
        ptr += DB_SYS_INFO_OFFSET + sizeof(edge) * sys_info.db_cnt_edges;

        memcpy(ptr,(char*) edges, sizeof(edge));

        ++sys_info.db_cnt_edges;
        sys_info.db_last_modified = time(0);
        core_write_sys_info(db_context, sys_info);
    }
    else{
        error("Can't write NODE to DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_read_db(db_context* db_context, char* data, int ptr_start, int size){
    if(data == NULL){
        error("Data must be allocated before READ");
        return FAILURE;
    }
    
    // 1. Attach database
    if (core_attach_db(db_context) == SUCCESS) {
        char* ptr = db_context->mem_ptr;
        // 2. Read Memory 
        memcpy(data, ptr + ptr_start, size);
    }
    else{
        error("Can't read from DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_read_node_db(db_context* db_context, int id, nd* node){
    if (core_attach_db(db_context) == SUCCESS) {      
        db_sys_info sys_info = {};
        core_read_sys_info(db_context, &sys_info);

        node->data = malloc(TEMP_SIZE);

        char* ptr = db_context->mem_ptr + NODES_OFFSET;
        for(int i = 0; i < id + 1; ++i){
            memcpy(&node->node_id, ptr, sizeof(int));
            ptr += sizeof(int);
            #ifdef DEBUG
                printf("[DBG]:> ID: %d\n", node->node_id);
            #endif
            memcpy(&node->data_type, ptr, sizeof(int));
            ptr += sizeof(int);
            #ifdef DEBUG
                printf("[DBG]:> TYPE: %d\n", node->data_type);
            #endif
            memcpy(&node->data_sz, ptr, sizeof(int));
            ptr += sizeof(int);
            #ifdef DEBUG
                printf("[DBG]:> SIZE: %d\n", node->data_sz);
            #endif
            memcpy(node->data, ptr, node->data_sz);
            ((char*) node->data)[node->data_sz] = '\0';
            #ifdef DEBUG
                printf("ID: %s\n", (char*) node->data);
            #endif
            ptr += node->data_sz;
        }
    }
    else{
        error("Can't read from DB");
        return FAILURE;
    }

    return SUCCESS;
}

int core_read_edge_db(db_context* db_context, int id, edge* edge){
    if (core_attach_db(db_context) == SUCCESS) {      
        db_sys_info sys_info = {};
        core_read_sys_info(db_context, &sys_info);

        char* ptr = db_context->mem_ptr + NODES_OFFSET;
        for(int i = 0; i < id + 1; ++i){
            memcpy(edge, ptr, sizeof(pair));
            ptr += sizeof(pair);
        }
    }
    else{
        error("Can't read from DB");
        return FAILURE;
    }

    return SUCCESS;
}