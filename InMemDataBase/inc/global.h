#ifndef GLOBAL_H
#define GLOBAL_H
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

//#define DEBUG

#define DEFAULT_DB_SIZE 1024 * 16
#define COMMAND_SIZE 512
#define TEMP_SIZE 128

#define DB_SYS_INFO_OFFSET 32
#define NODES_OFFSET 512

#define TRUE 1
#define FALSE 0

#define true 1
#define false 0

#define SUCCESS 1
#define FAILURE 0
#define IPC_FAIL -1

#define MAGIC "kra"
#define MAGIC_CH_1 'k'
#define MAGIC_CH_2 'r'
#define MAGIC_CH_3 'a'

#define ND_TYPE_DEFAULT 1

#endif