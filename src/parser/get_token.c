/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 03:02:01 by tanas             #+#    #+#             */
/*   Updated: 2023/10/08 16:48:25 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the character is an operator
static bool	is_opr(char c)
{
	return (c == '<' || c == '|' || c == '>');
}

// check if the character is a quote
static char	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}

static void	handle_opr(char **scan, int *in_quote)
{
	if (!*in_quote)
		*in_quote = **scan;
	else if (*in_quote == **scan)
		*in_quote = 0;
}

/**
 * @brief Determines the type of a token in the input string.
 *
 * The function scans the input string to classify it as an operator,
 * quoted string, or general text. The 'scan' pointer is advanced to the
 * end of the detected token.
 *
 * @param scan Pointer to the current position in the input string.
 *
 * @return A character representing the type of token found:
 *         - '<' for less than operator.
 *         - '+' for double greater than (i.e., append) operator.
 *         - '-' for double less than (i.e here_doc) operator.
 *         - 'a' for any other non-operator token.
 *         - '0' for an end-of-string or unclosed quote.
 */
static char	find_type(char **scan)
{
	int	in_quote;

	in_quote = 0;
	if (!**scan)
		return (0);
	else if (is_opr(**scan))
	{
		if (!ft_strncmp(*scan, ">>", 2) && ((*scan)++))
			return ('+');
		else if (!ft_strncmp(*scan, "<<", 2) && ((*scan)++))
			return ('-');
		return (**scan);
	}
	while (**scan)
	{
		if (is_quote(**scan))
			handle_opr(scan, &in_quote);
		if (!in_quote && (!scan[0][1]
			|| ft_is_whitespace(scan[0][1]) || is_opr(scan[0][1])))
			break ;
		*scan += 1;
	}
	if (in_quote)
		return (print_error("unclosed quote", NULL), 'u');
	return ('a');
}

/**
 * @brief Extracts and classifies the next token from the buffer.
 *
 * This function scans the input buffer, skipping any leading whitespace,
 * to find and classify the next token. The token is categorized using
 * the find_type() helper function. The ts and token_end pointers are set
 * to the bounds of the found token. After classification, the buffer_start
 * pointer is advanced to the start of the next token or the end of the buffer.
 *
 * @param bs Pointer to the current position in the buffer.
 * @param be Pointer to the end of the buffer.
 * @param ts Pointer to store the beginning of the detected token.
 * @param te Pointer to store the end of the detected token.
 *
 * @return Character code representing the type of token extracted.
 */
char	get_token(char **bs, char *be, char **ts, char **te)
{
	char	token_type;
	char	*scan;

	scan = *bs;
	while (scan < be && ft_is_whitespace(*scan))
		scan++;
	if (ts)
		*ts = scan;
	token_type = find_type(&scan);
	if (*scan)
		scan++;
	if (te)
		*te = scan;
	while (scan < be && ft_is_whitespace(*scan))
		scan++;
	*bs = scan;
	return (token_type);
}
