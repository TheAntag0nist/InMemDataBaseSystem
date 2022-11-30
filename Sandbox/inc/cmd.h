#ifndef CMD_H
#define CMD_H
#include "global.h"
#include "core.h"
#include "log.h"

char command[COMMAND_SIZE];
char temp[TEMP_SIZE];

// 1. Global database context
static char flag_db_enabled = false;
db_context context;

void help();
void main_loop();
void create_node();
void open_database();
void create_database();
void display_node();
void delete_node();
void link_node();
void save_db_cmd();

#endif