/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:52:34 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/16 23:51:02 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO fix remove_quote logic, echo to see how shell does parameter expansion
/**
 * Determines if a part of the provided string range is enclosed within quotes.
 * If a quoted section is found, it modifies the string by truncating it at the
 * closing quote, making the closing quote the new end of the string.
 *
 * @param q   Start pointer of the string range.
 * @param eq  End pointer of the string range (exclusive).
 *
 * @return    The type of quote character ('"' or '\'') if a closed quoted section is
 *            found. Otherwise, returns 0.
 */
static char	__is_quoted(char *q, const char *eq)
{
	char	quote;

	quote = 0;
	while (q < eq)
	{
		// if found a matching quote 0 the quote
		if (!(*q - quote))
			return (*q);
		// If no quote character has been found yet, check for one.
		if (!quote && (*q == '"' || *q == '\''))
			quote = *q;
		q++;
	}
	// return 0 if it is not quoted or is quoted but not closed
	return (0);
}

/**
 * Removes specified quote characters from a given string.
 *
 * This function processes the input string to eliminate specified quote characters
 * and returns a newly allocated string without the quotes. It's the caller's responsibility
 * to free the memory of the original string.
 *
 * Note: Currently, the function supports a maximum string length of 4096 due to hardcoded buffer size.
 *
 * @param q      Pointer to the beginning of the string from which quotes are to be removed.
 * @param eq     Pointer to the end of the string (just after the last character).
 *
 * @return       A newly allocated string with quotes removed or NULL if memory allocation fails.
 */
char *remove_quotes(char *q, char *eq)
{
	char unquoted[4096]; //! hardcoding for days
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
				break;
			}
			else
				unquoted[i++] = *q++;
		}
	}
	return(ft_strdup(unquoted));
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
	char	*delimiter;
	size_t	i;
	size_t	len;

	i = 0;
	len = eq - q;
	// Allocate memory for the delimiterimeter
	delimiter = malloc(sizeof(char) * (len + 1));
	if (!delimiter)
	{
		write(STDERR_FILENO, "malloc failed in get_delimiter\n", 25);
		return (NULL);
	}
	// Copy characters from range to delimiter
	while (i < len)
		delimiter[i++] = *q++;
	delimiter[i] = 0;
	return (delimiter);
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
void	here_doc(const int pipe_write, char *delimiter, t_env **env_list)
{
	char	*line;
	char	*temp;
	char	quote;

	quote = __is_quoted(delimiter, (delimiter + ft_strlen(delimiter)));
	// Remove quotes from the delimiter if any.
	if (quote)
		delimiter = remove_quotes(delimiter, delimiter + ft_strlen(delimiter));
	// If no delimiter is provided, it's considered a syntax error in Bash.
	if (!*delimiter)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected token `newline'\n", 56);
		return ;
	}
	// Continuously read input lines until the delimiter is matched.
	while (true)
	{
		line = readline(">");
		if (!line || (delimiter && !ft_strncmp(delimiter, line, get_len(delimiter, line))))
			break ;
		// If the delimiter isn't quoted, perform variable expansion.
		if (!quote)
		{
			temp = line;
			line = expand(line, line + ft_strlen(line), env_list, true);
			free(temp);
		}
		// Write the processed line to the provided file descriptor.
		write(pipe_write, line, ft_strlen(line));
		write(pipe_write, "\n", 1);
		free(line);
	}
	// Free the line containing the delimiter and the delimiter itself.
	free(line);
	free(delimiter);
}
