#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>

#include "ft_error.h"
#include "utils.h"
#include "cmdtable/type.h"

typedef struct s_token
{
    char *t; // mallocd needs to be freed aswell
    struct s_token *next;
} t_token;
/* creates a que of tokens to be formed into a simple command */
t_token *queue(char *tokens);

/* A simple command is an entry in the pipeline */
enum    type {OPR, WRD};
#define N_AVAILABLE_ARGS 32
typedef struct s_simple_command
{
    char        type; /* 0 operand, word 1 */
    char        *name; // Wcommands name
    char        *args[N_AVAILABLE_ARGS]; // argument array
    int         _rfiles[3]; /* 0 inFile, 1 outfile, 2 errfile */
    int         _background;
    struct s_simple_command *next;
}t_simple_command;

typedef struct s_command_table
{
    t_simple_command *sc;


    

}t_command_table;




#endif
