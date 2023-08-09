/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:52:34 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/09 12:03:01 by tanas            ###   ########.fr       */
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
 * @return    The type of quote character ('"' or '\'') if a closed quoted section is 
 *            found. Otherwise, returns 0.
 *
 * Note: This function modifies the input string by truncating it at the end of 
 * the quoted section, if found.
 */
 static char __is_quoted(char *q, char *eq) {
  char quote;

  quote = 0;
  while (q < eq) {
    // If current character matches the previously found quote type, end the string here.
    if (!(*q - quote)) {
      *q = 0; 
      return (quote);
    }
    // If no quote character has been found yet, check for one.
    if (!quote && (*q == '"' || *q == '\'')) 
      quote = *q;
    q++;
  }
  // return 0 if it is not quoted
  return (0);
}

/**
 * Removes the specified quote character from the provided delimiter string.
 * 
 * This function creates and returns a new string with the specified quotes
 * removed, freeing the memory of the original string.
 *
 * @param delimiter     The original string from which quotes are to be removed.
 * @param quote         The quote character to be removed from the string.
 * 
 * @return       A new string with the quotes removed. Returns NULL in case
 *               of memory allocation failure.
 */
char *remove_quote(char *delimiter, char quote) {
  size_t  size;
  size_t  i;
  char  *unquoted_delimiter;
  char  *temp; 

  i = 0;
  temp = delimiter;
  size = ft_strlen(delimiter);
  // Allocate memory for the unquoted delimiter.
  unquoted_delimiter = malloc(sizeof(char) * (size));
  if (!unquoted_delimiter) {
    write(STDERR_FILENO, "malloc failed in remove_quote\n", 30);
    return (NULL);
  }
  // Copy characters from original string, skipping the quotes.
  while (i < size) {
    if (*delimiter == quote)
      delimiter++; 
    unquoted_delimiter[i++] = *delimiter++;
  } 
  unquoted_delimiter[i] = 0;
  // freeing the original delimiterimiter
  free(temp);
  return (unquoted_delimiter);
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
char *get_delimiter(char *q, char *eq) {
  char    *delimiter;
  size_t  i;
  size_t  len;

  i = 0;
  len = eq - q;
  // Allocate memory for the delimiterimeter
  delimiter = malloc(sizeof(char) * (len + 1));
  if (!delimiter) {
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
 * @param envp        Environment variables for potential expansion.
 */
void here_doc(int pipe_write, char *delimiter, char **envp) {
  char *line;
  char *temp;
  char  quote;

  // Determine if the delimiter is quoted and identify the quote character.
  // If not quoted, __is_quoted returns 0.
  quote = __is_quoted(delimiter, (delimiter + ft_strlen(delimiter))); 
  // Remove quotes from the delimiter if any.
  if (quote)
    delimiter = remove_quote(delimiter, quote);
  // If no delimiter is provided, it's considered a syntax error in Bash.
  if (!*delimiter){
    write(STDERR_FILENO, "minishell: syntax error near unexpected token `newline'\n", 56);
    return ;
  }
  // Continuously read input lines until the delimiter is matched.
  while (true) {
    line = readline(">"); 
    if (!line || (delimiter && !ft_strncmp(delimiter, line, get_len(delimiter, line))))
      break;
    // If the delimiter isn't quoted, perform variable expansion.
    if (!quote) { 
     temp = line;
     line = expand(line, line + ft_strlen(line), envp); 
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

