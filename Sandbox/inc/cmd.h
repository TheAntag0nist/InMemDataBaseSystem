#ifndef CMD_H
#define CMD_H
#include "global.h"
#include "core.h"
#include "log.h"

char command[COMMAND_SIZE];
char temp[TEMP_SIZE];

// 1. Global database context
static char flag_db_enabled = false;
static char flag_db_server = false;
db_context context;

void main_loop();
// 0. Global commands
void get_system_info();
void help();

// 1. Database functions
void create_database_cmd();
void open_database_cmd();
void save_database_cmd();

// 2. Node functions
void get_near_nodes_cmd();
void display_node_cmd();
void create_node_cmd();
void delete_node_cmd();
void link_node_cmd();
void find_node_cmd();
void get_edge_cmd();


#endif