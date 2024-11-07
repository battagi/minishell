#ifndef BUILTIN_H
#define BUILTIN_H
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
//achraf
typedef enum e_token_type {
    WORD, //0
    S_QUOTE, //1
    D_QUOTE, //2
    SPACES, //3
    ENV, //4
    PIPE, //5
    RED_IN, //6
    RED_OUT, //7
    RED_APP, //8
    HERE_DOC //9
} t_token_type;


typedef struct s_token{
    char *value;
    t_token_type type;
    struct s_token *next;

} t_token;


//for the environment
typedef struct s_env{
    char *key;
    char *value;
    struct s_env *next;
} t_env;



typedef struct s_red{
    char *value;
    t_token_type type;
    struct s_red *next;
    
} t_red;

typedef struct s_command{
    char **args;
    t_red *red;
    struct s_command *next;
} t_command;

// ....................................................

typedef struct s_cmd
{
    char                **cmd;
    // t_in                *in;
    // t_out                *out;
    struct s_cmd        *next;
    struct s_cmd        *prev;
    int                    fd;
}                        t_cmd;


// typedef enum s_in_type
// {
//     RD_IN,
//     H_IN,
// }                        t_in_type;
// typedef enum s_out_type
// {
//     RD_OUT,
//     AP_OUT,
// }                        t_out_type;
// typedef struct s_in
// {
//     char                *input;
//     t_in_type            type;
//     struct s_in            *next;
//     struct s_in            *prev;
// }                        t_in;
// typedef struct s_out
// {
//     char                *output;
//     t_out_type            type;
//     struct s_out        *next;
//     struct s_out        *prev;
// }                        t_out;
#endif