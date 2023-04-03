#include "../../include/ft_error.h"


void	mem_error(void *ptr)
{
	if (!ptr)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
	}
}
