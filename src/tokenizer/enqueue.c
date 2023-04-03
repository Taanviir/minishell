#include "../../include/token.h"

//* add a token to the queue, note that token is not created
//* nor type is set here, a ready token is needed
void	enqueue(t_token *token, t_queue *cmd_q)
{
	t_token *old_last = cmd_q->last;
	cmd_q->last = token;
	if (q_is_empty(cmd_q))
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

/* program flowchart from inputting a string -> queue
char *s -> split -> char cmd[][]
 = cmd[1], cmd[2], cmd[3] ....
mk_token(cmd[1]: token)
mk_token{
	malloc
	set_token_type()
	return token
}
enqueue(token)
.
.
.
[cmd_q]





adfa


 */
