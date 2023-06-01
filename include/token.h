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
#include "token/type.h"

/* Token node */
typedef struct s_token
{
	char			*name;
	u_int8_t		type; // can be either word or operator
	u_int8_t		stype; // sub-type
	struct s_token	*next;
}	t_token;

/* Token API */
// TODO testing
t_token	*mktoken(char *token, char **envp);	// creates a node from a string, sets type
void	set_token_type(t_token *token, char **envp);	// set tokens type
void	free_token(t_token *token);	// free token

/* Command queue (FIFO) */
typedef struct s_queue
{
	t_token		*first;	// first token in the queue
	t_token		*last;	// last token in the stack
	u_int8_t		size;	// stack size
}	t_queue;

/* Command table 2 queues of words and operands */
typedef struct s_ctable
{
	t_queue		*words;
	t_queue		*operands;
	u_int8_t	size;
} t_ctable;

/* queue API */
// TODO testing
void		_enqueue(t_token *token, t_queue *cmd_q);	// add token to stack
t_token	*_dequeue(t_queue *cmd_q);
t_queue	*create_command_queue(char **arguments);

/* not yet implemented */
void	free_queue(t_queue *cmd_q);	// free and free all tokens
bool	q_isempty(t_queue *cmd_q);	// check if stack is empty


#endif
