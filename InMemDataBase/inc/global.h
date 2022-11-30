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

#define DEFAULT_DB_SIZE 1024
#define COMMAND_SIZE 512
#define TEMP_SIZE 128

#define TRUE 1
#define FALSE 0

#define true 1
#define false 0

#define SUCCESS 1
#define FAILURE 0
#define IPC_FAIL -1

#endif