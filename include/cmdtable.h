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
    int        type; /* 0 operand, word 1 */
    struct s_token *next;
} t_token;
/* creates a que of tokens to be formed into a simple command */
t_token *queue(char *tokens);
/* A simple command is an entry in the pipeline */
enum    token_type {OPR, WRD};
/*          (token)
             /   \
           OPR   WRD
Based on a list of operanads and words a simple command can be made
 */

#define N_AVAILABLE_ARGS 32
typedef struct s_simple_command
{
    char        *name; // Wcommands name
    int         size_of_args;
    char        *args[N_AVAILABLE_ARGS]; // argument array
    int         _rfiles[3]; /* 0 inFile, 1 outfile, 2 errfile array of file descriptors to redirect a stream to, (ex. direct stdin to pipe)*/
    int         _background;
    struct s_simple_command *next;
}t_simple_command;

typedef struct s_command_table
{
    t_simple_command *sc;




}t_command_table;

/* token functions */



#endif
