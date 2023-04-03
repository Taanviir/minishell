#ifndef TOKEN_H
#define TOKEN_H

//* includes
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>

//* local includes
#include "ft_error.h"
#include "utils.h"
#include "token/type.h"

//* Token node
typedef struct s_token
{
	char			*s_token;
	u_int8_t		type;
	struct s_token	*next;
}	t_token;

//* Token API
// TODO testing
t_token	*mk_token(char *token, char **envp);							// creates a node from a string, sets type
void	set_token_type(t_token *token, char **envp);	// set tokens type
void	free_token(t_token *token);						// free token

//* Command queue (FIFO)
typedef struct s_queue
{
	t_token		*first;	// first token in the queue
	t_token		*last;	// last token in the stack
	u_int8_t	size;	// stack size
}	t_queue;

//* queue API
// TODO testing
void	enqueue(t_token *token, t_queue *cmd_q);	// add token to stack
t_token	*dequeue(t_queue *cmd_q);				// returns and removes first token from queue (FIFO)
// not yet implemented
void	free_queue(t_queue *cmd_q);				// free and free all tokens
bool	q_is_empty(t_queue *cmd_q);					// check if stack is empty
t_queue	*create_queue(void);						// create an empty queue


#endif
