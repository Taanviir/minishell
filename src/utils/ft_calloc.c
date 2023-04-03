#include "../../include/utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;

	if (size && (SIZE_MAX / size) > count)
	{
		dest = malloc(size * count);
		if (!dest)
			return (NULL);
		ft_memset(dest, 0, size * count);
	}
	else
		return (NULL);
	return (dest);
}
