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
typedef struct _s_token
{
	char			*s_token;
	u_int8_t		type;
	struct _s_token	*next;
}	_t_token;

/* Token API */
// TODO testing
_t_token	*_mk_token(char *token, char **envp);	// creates a node from a string, sets type
void	set_token_type(_t_token *token, char **envp);	// set tokens type
void	free_token(_t_token *token);	// free token

/* Command queue (FIFO) */
typedef struct _s_queue
{
	_t_token		*first;	// first token in the queue
	_t_token		*last;	// last token in the stack
	u_int8_t		size;	// stack size
}	_t_queue;

/* queue API */
// TODO testing
void		_enqueue(_t_token *token, _t_queue *cmd_q);	// add token to stack
_t_token	*_dequeue(_t_queue *cmd_q);
_t_queue	*create_command_queue(char **arguments);

/* not yet implemented */
void	free_queue(_t_queue *cmd_q);	// free and free all tokens
bool	q_isempty(_t_queue *cmd_q);	// check if stack is empty


#endif
