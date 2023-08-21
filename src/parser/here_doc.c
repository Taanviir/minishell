/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:52:34 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/21 18:02:28 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Determines if a part of the provided string range is enclosed within quotes.
 * If a quoted section is found, it modifies the string by truncating it at the
 * closing quote, making the closing quote the new end of the string.
 *
 * @param q   Start pointer of the string range.
 * @param eq  End pointer of the string range (exclusive).
 *
 * @return    The type of quote character ('"' or '\'') if a closed quoted
 *            section is found. Otherwise, returns 0.
 */
static char	__is_quoted(char *q, const char *eq)
{
	char	quote;

	quote = 0;
	while (q < eq)
	{
		if (!(*q - quote))
			return (*q);
		if (!quote && (*q == '"' || *q == '\''))
			quote = *q;
		q++;
	}
	return (0);
}

/**
 * Removes specified quote characters from a given string.
 *
 * This function processes the input string to eliminate specified quote
 * characters and returns a newly allocated string without the quotes.
 * It's the caller's responsibility to free the memory of the original string.
 *
 * Note: Currently, the function supports a maximum string length of 4096
 * due to hardcoded buffer size.
 *
 * @param q Pointer to the beginning of the string from which quotes are 
 *          to be removed.
 * @param eq Pointer to the end of the string (just after the last character).
 *
 * @return A newly allocated string with quotes removed or NULL if memory
 *         allocation fails.
 */
char	*remove_quotes(char *q, char *eq)
{
	char	unquoted[4096];
	size_t	i;
	int		in_quote;

	i = 0;
	memset(unquoted, 0, 4096);
	in_quote = 0;
	while (q < eq)
	{
		if (*q == '\'' || *q == '\"')
			in_quote = *q++;
		else
			unquoted[i++] = *q++;
		while (q < eq && in_quote)
		{
			if (!(in_quote - *q))
			{
				q++;
				break ;
			}
			else
				unquoted[i++] = *q++;
		}
	}
	return (ft_strdup(unquoted));
}

/**
 * Extracts a substring from the provided string range [q, eq).
 *
 * This function creates a new string which is a subset of the original string,
 * based on the provided start and end pointers. The returned string does not
 * include the character pointed to by eq.
 *
 * @param q   Start pointer of the string segment to be extracted.
 * @param eq  End pointer of the string segment to be extracted.
 *
 * @return    A new string containing the extracted segment. Returns NULL if
 *            memory allocation fails.
 */
char	*get_delimiter(char *q, const char *eq)
{
	char	*del;
	size_t	i;
	size_t	len;

	i = 0;
	len = eq - q;
	del = malloc(sizeof(char) * (len + 1));
	if (!del)
	{
		write(STDERR_FILENO, "malloc failed in get_delimiter\n", 25);
		return (NULL);
	}
	while (i < len)
		del[i++] = *q++;
	del[i] = 0;
	return (del);
}

static void	__dumb(char **line, t_env **env_list)
{
	char	*temp;

	temp = *line;
	*line = expand(*line, *line + ft_strlen(*line), env_list, true);
	free(temp);
}

/**
 * Implements the here document ("here-doc") feature for the shell.
 * Reads input lines until the delimiter is matched, performs variable expansion
 * (if the delimiter isn't quoted), and writes to the specified file descriptor.
 *
 * @param pipe_write  File descriptor to which the function writes the input.
 * @param del         Delimiter string used to terminate input.
 * @param env_list        Environment variables for potential expansion.
 */
void	here_doc(const int pipe_write, char *del, t_env **env_list)
{
	char	*line;
	char	quote;

	quote = __is_quoted(del, (del + ft_strlen(del)));
	if (quote)
		del = remove_quotes(del, del + ft_strlen(del));
	if (!*del && !print_error(DELI_ERROR, NULL))
		return ;
	signal(SIGINT, signal_handler_heredoc);
	line = NULL;
	while (g_exit_status != QUIT_HEREDOC)
	{
		line = readline("> ");
		if (true && !line || ((del && !ft_strncmp(del, line, get_len(del, line)))
				&& !close(pipe_write)))
			break ;
		if (!quote)
			__dumb(&line, env_list);
		ft_putendl_fd(line, pipe_write);
		free(line);
	}
	printf("L: %s D: %s\n", line, del);
	free(line);
	free(del);
}
