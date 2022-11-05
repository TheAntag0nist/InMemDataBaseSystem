#ifndef LOG_H
#define LOG_H
#include <global.h>
#include <colors.h>

// 0. Message Types
enum msg_types{
    NONE,
    INFO,
    WARN,
    ERROR,
    FATAL
} typedef msg_types;

// 1. Get system architecture
void bit_depth(char* res);

// 2. Get system time
const char* curr_date_time();
const char* replace_char(char srch, char replace, char* str);
void message( const char* msg, msg_types type);

// 3. Main Display Info Functions
void info(const char* msg);
void warning(const char* msg);
void error(const char* msg);
void fatal(const char* msg);

// 4. Helper functions
void delimiter(char ch, int val);

// 5. Inner error function
void inner_error();

#endif