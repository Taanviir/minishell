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
#include "interpreter/type.h"

typedef struct	s_token
{
	char			*token; // mallocd needs to be freed aswell
	int				identifier; /* 0 operand, word 1 */
	struct s_token	*next;
}	t_token;
/* A simple command is an entry in the pipeline */
enum    token_type {OPR, WRD};
/*          (token)
             /   \
           OPR   WRD
Based on a list of operanads and words a simple command can be made
 */

t_token	*tkn_queue(const char *input);

#define N_AVAILABLE_ARGS 32
typedef struct s_simple_command
{
	char	*name; // Wcommands name
	int		size_of_args;
	char	*args[N_AVAILABLE_ARGS]; // argument array
	int		rfiles[3]; /* 0 inFile, 1 outfile, 2 errfile array of file descriptors to redirect a stream to, (ex. direct stdin to pipe)*/
	int		background;
	struct s_simple_command *next;
}t_simple_command;

/* token functions */



#endif
