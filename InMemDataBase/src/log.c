#include "log.h"

// 1. Get architecture
void bit_depth(char* res){
    if(sizeof(int*) == 4)
        strcpy(res, "Bit Death: x86");
    else if(sizeof(int*) == 8)
        strcpy(res, "Bit Death: x64");
}

// 2. Get current date
const char* curr_date_time(){
    time_t tm = time(NULL);
    return (const char*) ctime(&tm);
}

// 3. Replace char
const char* replace_char(char srch, char replace, char* str){
    for(int i = 0; i < strlen(str); ++i)
        if(str[i] == srch)
            str[i] = replace;

    return str;
}

// 4. Universal message function
void message( const char* msg, msg_types type){
    // recalculate size of arrays
    char msg_type_str[60];
    char temp_str[40];

    msg_type_str[0] = '\0';
    temp_str[0] = '\0';

    switch (type)
    {
        case NONE:
        #ifdef unix
            //set_color(GREEN);
            printf(BOLD F_GREEN);
        #endif
            strcat(temp_str, "[ ");
            strcat(temp_str, curr_date_time());
            strcat(temp_str, "]");
            strcpy(msg_type_str, temp_str);
            break;
        case INFO:
        #ifdef unix
            //set_color(GREEN);
            printf(BOLD F_GREEN);
        #endif
            strcat(temp_str, "[ INF ");
            strcat(temp_str, curr_date_time());
            strcat(temp_str, "]");
            strcpy(msg_type_str, temp_str);
            break;
        case WARN:
        #ifdef unix
            //set_color(YELLOW);
            printf(BOLD F_YELLOW);
        #endif
            strcat(temp_str, "[ WRN ");
            strcat(temp_str, curr_date_time());
            strcat(temp_str, "]");
            strcpy(msg_type_str, temp_str);
            break;
        case ERROR:
        #ifdef unix
            //set_color(RED);
            printf(BOLD F_RED);
        #endif
            strcat(temp_str, "[ ERR ");
            strcat(temp_str, curr_date_time());
            strcat(temp_str, "]");
            strcpy(msg_type_str, temp_str);
            break;
        case FATAL:
        #ifdef unix
            //set_color(RED);
            printf(BOLD F_RED);
        #endif
            strcat(temp_str, "[ FTL ");
            strcat(temp_str, curr_date_time());
            strcat(temp_str, "]");
            strcpy(msg_type_str, temp_str);
            break;
    }


    replace_char( '\n', ' ', msg_type_str);
    printf("%s\t", msg_type_str);

    #ifdef unix
        //reset_color();
        printf(RESET);
    #endif

    printf("%s\n", msg);
}

// 5. Info message
void info(const char* msg){
    message(msg, INFO);
}

// 6. Warnings message
void warning(const char* msg){
    message(msg, WARN);
}

// 7. Error message
void error(const char* msg){
    message(msg, ERROR);
    inner_error();
}

// 8. Fatal message
void fatal(const char* msg){
    message(msg, FATAL);
    inner_error();
    exit(-1);    
}

// 9. Check delimiter
void delimiter(char ch, int val){
    if(val <= 0 )
        val = 33;

    for(int i = 0; i < val; ++i)
        printf("%c",ch);
    printf("\n");
}

// 10. Default inner error message
void inner_error(){
    printf(BOLD F_RED);
    printf("[ERRNO] ");

    #ifdef unix
        //reset_color();
        printf(RESET);
    #endif
    
    printf("last_error = %d\n", errno);
}