#include "../../include/interpreter.h"

/* QUEUE FIFO implementation API needs to be made as it is used alot */
/* complete with freeing functions */

/* converts a struct to a node */
static t_node	*_node_wrapper(void *new)
{
	t_node	*temp;

	temp = malloc(sizeof(t_node));
	if (!temp)
		return (NULL);
	temp->data = new;
	temp->next = NULL;
	return (temp);
}

/* returns an empty queue (t_queue) */
t_queue	*create_queue(void)
{
	t_queue	*new_queue;

	new_queue = malloc(sizeof(t_queue));
	if (!new_queue)
		return (NULL);
	new_queue->first = NULL;
	new_queue->last = NULL;
	new_queue->size = 0;
	return (new_queue);
}

/* adds a node to the queue */
void	enqueue(void *new, t_queue *q)
{
	t_node	*temp;

	temp = _node_wrapper(new);
	if (q->last) // this is the 2nd new onwards
	{
		q->last->next = temp;
		q->size++;
	}
	if (!q->first)
	{
		q->first = temp; // temp must be first one hmmmm!
		q->last= q->first;
		q->size++;
	}
	else
		q->last= temp;
}

/* removes the first node in the que and returns it */
// t_node*	dequeue(t_queue *q)

