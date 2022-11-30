#include <cmd.h>

void main_loop(){
    while(true){
        printf("cmd:> ");
        scanf("%s", command);

        if(!strcmp(command, "help")){
            help();
            continue;;
        }

        if(!strcmp(command, "create_node")){
            create_node();
            continue;;
        }

        if(!strcmp(command, "create_database")){
            create_database();
            continue;;
        }

        if(!strcmp(command, "open_database")){
            open_database();
            continue;
        }

        if(!strcmp(command, "save_db")){
            save_db_cmd();
            continue;;
        }

        if(!strcmp(command, "exit")){
            info("Exit from program");
            if(flag_db_enabled)
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
}

void create_node(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Create node");
    printf("\tEnter node data: ");
    scanf("%s", temp);
}

void open_database(){
    if(flag_db_enabled){
        info("Previous database was closed");
        destroy_db(&context);
    }

    info("COMMAND -> Open database");
    printf("\tEnter database name: ");
    scanf("%s", temp);

    int id = 0;
    printf("\tEnter key: ");
    scanf("%d", &id);

    int res = connect_db(&context, temp, id);
    if(res == SUCCESS){
        info("Success!");
        flag_db_enabled = true;
    }
    else{
        error("Faillure!");
        flag_db_enabled = false;
    }
}

void create_database(){
    info("COMMAND -> Create database");
    printf("\tEnter database name: ");
    scanf("%s", temp);

    int id = 0;
    printf("\tEnter key: ");
    scanf("%d", &id);

    int res = connect_db(&context, temp, id);
    if(res == SUCCESS){
        info("Success!");
        flag_db_enabled = true;
    }
    else{
        error("Faillure!");
        flag_db_enabled = false;
    }
}

void display_node(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }
    
    info("COMMAND -> Display node");
    printf("\tEnter node ID: ");
    scanf("%s", temp);
}

void delete_node(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Delete node");
    printf("\tEnter node ID: ");
    scanf("%s", temp);
}

void link_node(){
    if(!flag_db_enabled){
        error("Database is not enabled");
        return;
    }

    info("COMMAND -> Link nodes");
    printf("\tEnter first node ID: ");
    scanf("%s", temp);
}

void save_db_cmd(){
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