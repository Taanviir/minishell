/*
Bash Grammar could be written in a format called "Backus-Naur Form"

cmd [arg]* [|cmd [arg]* ]* [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]
- an example of shell grammar in Backus-Naur form
*/

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

#include "utils.h"

/* A token is a character or a group of characters recognized
from the input stream. Identifier = primarytype_secondarytype
 */
typedef struct	s_token
{
	char			*token; // mallocd needs to be freed aswell
	u_int32_t		identifier; /* 0 operand, word 1 */
}	t_token;

enum	token_type {OPR, WRD};
/*          (token)
             /   \
           OPR   WRD
Based on a list of operanads and words a simple command can be made
 */

t_token	*create_token(char *token);
t_queue	*tokenizer(char *input);

#define N_AVAILABLE_ARGS 32
/* A simple command is an entry in the pipeline */
typedef struct s_simple_command
{
	char	*name; // commands name
	int		size_of_args;
	char	*args[N_AVAILABLE_ARGS]; // argument array
	int		rfiles[3]; /* 0 inFile, 1 outfile, 2 errfile array of file descriptors to redirect a stream to, (ex. direct stdin to pipe)*/
	int		background;
	struct s_simple_command *next;
}t_simple_command;

t_queue	*parse(char *input); /* Parses the token queue into a queue of simple commands */

/* token functions */



#endif

// TODO queue needs to be made into an FIFO API since its reused
