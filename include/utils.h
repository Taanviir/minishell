#ifndef UTILS_H
#define UTILS_H

//* includes
#include <stdlib.h>
#include <stdint.h>
#include "ft_error.h"

size_t	ft_strlen(char *s);						// string size
char	*ft_strlcpy(char *dest, const char *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *dest, int c, size_t len);
char	*ft_strcat(char *dest, char *src);
int		ft_strncmp(char *s1, char *s2, int n);

/* QUEUE FIFO implementation */
typedef struct s_node
{
	void			*data; /* can be any type of struct */
	struct s_node	*next;
}	t_node;
typedef struct s_queue
{
	t_node	*first;
	t_node	*last;
	size_t	size;
}	t_queue;

t_queue	*create_queue(void);
void	enqueue(void *new, t_queue *q);

#endif

// TODO organize frees and errors
