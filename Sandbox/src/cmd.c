#include <cmd.h>

void main_loop(){
    flag_db_enabled = false;
    flag_db_server = false;

    while(true){
        command[0] = '\0';
        fflush(stdin);
        fflush(stdout);

        printf("cmd:> ");
        scanf("%s", command);

        if(!strcmp(command, "help")){
            help();
            continue;;
        }

        if(!strcmp(command, "create_node")){
            create_node_cmd();
            continue;;
        }

        if(!strcmp(command, "create_database")){
            create_database_cmd();
            continue;;
        }

        if(!strcmp(command, "open_database")){
            open_database_cmd();
            continue;
        }

        if(!strcmp(command, "save_db")){
            save_database_cmd();
            continue;;
        }

        if(!strcmp(command, "find_node")){
            find_node_cmd();
            continue;
        }

        if(!strcmp(command, "link_node")){
            link_node_cmd();
            continue;
        }

        if(!strcmp(command, "get_edge")){
            get_edge_cmd();
            continue;
        }

        if(!strcmp(command, "get_near_nodes")){
            get_near_nodes_cmd();
            continue;
        }

        if(!strcmp(command, "get_near_nodes")){
            get_near_nodes_cmd();
            continue;
        }

        if(!strcmp(command, "get_system_info")){
            get_system_info();
            continue;
        }

        if(!strcmp(command, "exit")){
            info("Exit from program");
            if(flag_db_enabled && flag_db_server)
                destroy_db(&context);
            break;
        }

        error("Unknown command");
    }
}

void help(){
    info("COMMAND -> Help command");
    printf("\tcreate_node - create a node command\n");
    printf("\tcreate_database - create a database command\n");
    printf("\topen_database - open a database command\n");
    printf("\tdisplay_node - display node command\n");
    printf("\tdelete_node - delete node command\n");
    printf("\tlink_node - link nodes command\n");
    printf("\tfind_node - find node command\n");
    printf("\tget_near_nodes - get near nodes command\n");
    printf("\tget_system_info - get database system info command\n");
    printf("\tget_edge - get edge command\n");
}

void create_node_cmd(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Create node");
    printf("\tEnter node data: ");
    scanf("%s", temp);

    db_sys_info sys_info = {};
    get_database_system_info(&context, &sys_info);
    node_counter = sys_info.db_cnt_nodes;

    nd* created_node = create_node();
    created_node->data_sz = strlen(temp) + 1;
    created_node->data = malloc(created_node->data_sz);
    created_node->data_type = ND_TYPE_DEFAULT;
    strcpy(created_node->data, temp);

    add_node(&context, created_node);
    display_node(created_node);
}

void open_database_cmd(){
    if(flag_db_enabled){
        info("Previous database was closed");
        if(flag_db_server)
            destroy_db(&context);
    }

    info("COMMAND -> Open database");
    printf("\tEnter database name: ");
    scanf("%s", temp);

    int id = 0;
    printf("\tEnter key: ");
    scanf("%d", &id);

    printf("\tResult DATABASE NAME: %s\n", temp);
    printf("\tResult DATABASE ID: %d\n", id);

    int res = connect_db(&context, temp, id);
    if(res == SUCCESS){
        info("Success!");
        flag_db_enabled = true;

        get_system_info();
        db_sys_info sys_info = {};
        get_database_system_info(&context, &sys_info);
        node_counter = sys_info.db_cnt_nodes;
    }
    else{
        error("Faillure!");
        flag_db_enabled = false;
    }
}

void create_database_cmd(){
    info("COMMAND -> Create database");
    printf("\tEnter database name: ");
    scanf("%s", temp);

    int id = 0;
    printf("\tEnter key: ");
    scanf("%d", &id);

    printf("\tResult DATABASE NAME: %s\n", temp);
    printf("\tResult DATABASE ID: %d\n", id);

    int res = create_db(&context, temp, id);
    if(res == SUCCESS){
        info("Success!");
        flag_db_enabled = true;
        flag_db_server = true;
    }
    else{
        error("Faillure!");
        flag_db_enabled = false;
        flag_db_server = true;
    }
}

void display_node_cmd(){
    int id;
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }
    
    info("COMMAND -> Display node");
    printf("\tEnter node ID: ");
    scanf("%d", &id);

    db_sys_info sys_info = {};
    get_database_system_info(&context, &sys_info);

    if(id >= sys_info.db_cnt_nodes){
        warning("Incorrect NODE ID");
        return;
    }

    nd node = {};
    search_node(&context, id, &node);
    display_node(&node);
    if(node.data != NULL)
        free(node.data);
}

void delete_node_cmd(){
    int id;
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Delete node");
    printf("\tEnter node ID: ");
    scanf("%d", &id);

    // TODO: need to implement
}

void link_node_cmd(){
    int id_first_node = 0;
    int id_second_node = 0;
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Link nodes");
    printf("\tEnter first node ID: ");
    scanf("%d", &id_first_node);

    printf("\tEnter first node ID: ");
    scanf("%d", &id_second_node);

    edge new_edge = {id_first_node, id_second_node};
    add_edge(&context, &new_edge);
}

void save_database_cmd(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Save database");
    printf("\tEnter database file name: ");
    scanf("%s", temp);

    int res = save_db(&context, temp);
    if(res == SUCCESS)
        info("Successfully saved database to file");
}

void find_node_cmd(){
    int id = 0;
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Find node");
    printf("\tEnter node ID: ");
    scanf("%d", &id);

    db_sys_info sys_info = {};
    get_database_system_info(&context, &sys_info);

    if(id >= sys_info.db_cnt_nodes){
        warning("Incorrect NODE ID");
        return;
    }

    nd node = {0 ,0 , 0, 0};
    search_node(&context, id, &node);
    display_node(&node);
    if(node.data != 0)
        free(node.data);
}

void get_edge_cmd(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    int id = 0;    
    info("COMMAND -> Get near nodes");
    printf("\tEnter node ID: ");
    scanf("%d", &id);

    db_sys_info sys_info = {};
    get_database_system_info(&context, &sys_info);

    if(id >= sys_info.db_cnt_edges){
        warning("Incorrect EDGE ID");
        return;
    }

    edge edge = {};
    search_edge(&context, id, &edge);

    printf("\tEDGE NODE ID_1: %d\n", edge.first);
    printf("\tEDGE NODE ID_2: %d\n", edge.second);
}

void get_near_nodes_cmd(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    int id = 0;    
    info("COMMAND -> Get near nodes");
    printf("\tEnter node ID: ");
    scanf("%d", &id);

    db_sys_info sys_info = {};
    get_database_system_info(&context, &sys_info);

    if(id >= sys_info.db_cnt_nodes){
        warning("Incorrect NODE ID");
        return;
    }

    edge edge_data = {};
    for(int i = 0; i < sys_info.db_cnt_edges; ++i){
        search_edge(&context, i, &edge_data);
        if(edge_data.first == id || edge_data.second == id){
            printf("EDGE: %d <-> %d\n", edge_data.first, edge_data.second);
        }
    }
}

void get_system_info(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Get system info");
    db_sys_info sys_info = {};
    get_database_system_info(&context, &sys_info);

    printf("SYSTEM_INFO\n");
    printf("\tEDGES: %d\n", sys_info.db_cnt_edges);
    printf("\tNODES: %d\n", sys_info.db_cnt_nodes);
    char* created_tm = time_to_ascii(sys_info.db_created);
    printf("\tCREATED: %s", created_tm);
    char* modif_tm = time_to_ascii(sys_info.db_last_modified);
    printf("\tMODIFIED: %s", modif_tm);
}