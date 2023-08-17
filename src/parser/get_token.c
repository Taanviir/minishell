/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 07:38:08 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/17 00:00:23 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the character is an operator
static bool	is_opr(char c)
{
	return (c == '<' || c == '|' || c == '>' || c == '&' || c == ';');
}

// check if the character is a quote
static bool is_quote(char c) {
	return (c == '\'' || c == '"');
}

/**
 * @brief Determines the type of a token in the input string.
 * 
 * The function scans the input string to classify it as an operator, quoted string,
 * or general text. The 'scan' pointer is advanced to the end of the detected token.
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
	// if scan is at the end of the buffer, return 0
	if (!**scan)
		return (0);
	// if scan is at an operator, return the operator
	else if (is_opr(**scan))
	{
		if (!ft_strncmp(*scan, ">>", 2) && ((*scan)++))
			return ('+');
		else if (!ft_strncmp(*scan, "<<", 2) && ((*scan)++))
			return ('-');
		return (**scan);
	}
	// otherwise, scan until the end of the token
	while (scan[0][1] &&
			(in_quote || (!ft_is_whitespace(scan[0][1]) && !is_opr(scan[0][1]))))
	{
		// if the current character is a quote, toggle the in_quote flag
		if (!in_quote && is_quote(**scan))
			in_quote = **scan;
		// if the next character is the same quote, toggle the in_quote flag, checking for current character checking for current character will fail since it may be the end of the buffer 
		else if (in_quote && (scan[0][1] == in_quote))
			in_quote = 0;
		*scan += 1;
	}
	// if the token is unclosed, return 0
	if (in_quote) 
		return (0);
	return ('a');
}

/**
 * @brief Extracts and classifies the next token from the buffer.
 *
 * This function scans the input buffer, skipping any leading whitespace, to find
 * and classify the next token. The token is categorized using the find_type() helper
 * function. The token_start and token_end pointers are set to the bounds of the found 
 * token. After classification, the buffer_start pointer is advanced to the start of 
 * the next token or the end of the buffer.
 *
 * @param buffer_start Pointer to the current position in the buffer.
 * @param buffer_end Pointer to the end of the buffer.
 * @param token_start Pointer to store the beginning of the detected token.
 * @param token_end Pointer to store the end of the detected token.
 * 
 * @return Character code representing the type of token extracted.
 */
char	get_token(char **buffer_start, char *buffer_end, char **token_start,
               char **token_end)
{
	char	token_type;
	char	*scan;

	// set the scan pointer to the start of the buffer
	scan = *buffer_start;
	// skip leading whitespace
	while (scan < buffer_end && ft_is_whitespace(*scan))
		scan++;
	// if token_start is not NULL, set it to the current scan position
	if (token_start)
		*token_start = scan;
	// determine token type and move scan to the end of the token
	token_type = find_type(&scan);
	// if scan is not at the end of the buffer, advance it to the next token
	if (*scan)
		scan++;
	// if token_end is not NULL, set it to the current scan position
	if (token_end)
		*token_end = scan;
	// skip trailing whitespace
	while (scan < buffer_end && ft_is_whitespace(*scan))
		scan++;
	// set buffer_start to the current scan position
	*buffer_start = scan;
	return (token_type);
}
