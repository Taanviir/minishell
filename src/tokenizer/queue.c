#include "../../include/token.h"
#include <string.h>

/* return command queue size */
bool	q_isempty(_t_queue *cmd_q)
{
	return ((bool)cmd_q->size);
}

/* adds tokens formed by splitting up the arguments from stdin */
void	_enqueue(_t_token *token, _t_queue *cmd_q)
{
	_t_token *old_last = cmd_q->last;
	cmd_q->last = token;
	if (q_isempty(cmd_q))
	{
		cmd_q->first = token;
		cmd_q->last = token;
	}
	else
	{
		old_last->next = token;
	}
	cmd_q->size++;
}

/* removes a token from the command queue */
_t_token	*_dequeue(_t_queue *cmd_q)
{
	_t_token	*old_first;
	old_first = cmd_q->first;
	cmd_q->first = old_first->next;
	if (q_isempty(cmd_q))
		cmd_q->last = NULL;
	cmd_q->size--;
	return (old_first);
}

/* creats the command queue from the arguments recieved from stdin in the main
loop of the program */
_t_queue	*create_command_queue(char **arguments)
{
	_t_token	*new;

	while (*arguments)
	{
		new = malloc(sizeof(_t_token));
		if (!new)
			fputs("allocation error\n", stderr);
		new->s_token = malloc(sizeof(char) * strlen(*arguments));
		if (!new->s_token)
			fputs("allocation error\n", stderr);
		memcpy(new->s_token, *arguments, strlen(*arguments));
	}
	return (NULL);
}