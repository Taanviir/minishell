#include "../../include/utils.h"

static int	count_words(char *s, char delimiter);
static int	size_word(char **s, char delimiter);

//* handles commands from "./" by including an extra index at the end of the array for it
//! this fix might conflict with running the command later on
//! if reusing pipex remove "./" implementation from there and keep it here
char	**ft_split(char *command, char delimiter)
{
	char	**split;
	int		arr_size;
	int		i;
	int		wrd_len;

	arr_size = count_words(command, delimiter);
	split = malloc(sizeof(char *) * (arr_size + 2));
	mem_error(split);
	split[arr_size] = malloc(sizeof(char)); 
	mem_error(split[arr_size]);
	split[arr_size++] = "."; // store the "./" and increment index to store null
	split[arr_size] = NULL;
	i = 0;
	while (i < arr_size)
	{
		wrd_len = size_word(&command, delimiter);
		split[i] = malloc(sizeof(char) * wrd_len + 1);
		mem_error(split[i]);
		ft_strlcpy(split[i], command, wrd_len);
		i++;
		command += wrd_len;
	}
	return (split);
}

static int	count_words(char *s, char delimiter)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == delimiter)
			i++;
		if (s[i] && s[i] != delimiter)
		{
			n++;
			while (s[i] && s[i] != delimiter)
				i++;
		}
	}
	return (n);
}

static int	size_word(char **s, char delimiter)
{
	int	n;

	n = 0;
	while (**s == delimiter)
		(*s)++;
	while ((*s)[n] && (*s)[n] != delimiter)
		n++;
	return (n);
}
