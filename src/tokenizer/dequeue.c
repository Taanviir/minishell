#include "../../include/token.h"

//* check if its the last item in the stack
t_token	*dequeue(t_queue *cmd_q)
{
	t_token	*old_first;
	old_first = cmd_q->first;
	cmd_q->first = old_first->next;
	if (q_is_empty(cmd_q))
		cmd_q->last = NULL;
	cmd_q->size--;
	return (old_first);
}

