#include "../../include/token.h"
#include <string.h>

/* return command queue size */
bool	q_isempty(t_queue *cmd_q)
{
	return ((bool)cmd_q->size);
}

/* adds tokens formed by splitting up the arguments from stdin */
void	_enqueue(t_token *token, t_queue *cmd_q)
{
	t_token *old_last = cmd_q->last;
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
t_token	*_dequeue(t_queue *cmd_q)
{
	t_token	*old_first;
	old_first = cmd_q->first;
	cmd_q->first = old_first->next;
	if (q_isempty(cmd_q))
		cmd_q->last = NULL;
	cmd_q->size--;
	return (old_first);
}

/* creats the command queue from the arguments recieved from stdin in the main
loop of the program */
t_queue	*create_command_queue(char **arguments)
{
	t_token	*new;
	t_queue	*cmd_q;

	cmd_q = malloc(sizeof(t_queue));
	while (*arguments)
	{
		new = malloc(sizeof(t_token));
		if (!new)
			fputs("allocation error\n", stderr);
		new->name = malloc(sizeof(char) * strlen(*arguments));
		if (!new->name)
			fputs("allocation error\n", stderr);
		memcpy(new->name, *arguments, strlen(*arguments));
		_enqueue(new, cmd_q);
	}
	return (cmd_q);
}