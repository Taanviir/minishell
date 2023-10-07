/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:45:02 by tanas             #+#    #+#             */
/*   Updated: 2023/08/19 21:45:02 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the length of the longer of two strings.
 * 
 * @param str1 string 1
 * @param str2 string 2
 * @return the length of the longer string
 */
int	get_len(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	return (ft_strlen(str2));
}

/**
 * @brief Checks if a string is empty.
 * 
 * @param line string to check
 * @return true if the string is empty, false otherwise
 */
bool	is_empty(char *line)
{
	while (*line)
	{
		if (!ft_is_whitespace(*line))
			return (false);
		line++;
	}
	return (true);
}

/**
 * @brief Prints an error message to stderr.
 * 
 * @param err_msg error message to print
 * @param function function name to print
 * @return 0
 */
int	print_error(char *err_msg, char *function)
{
	ft_putstr_fd("minishell: ", 2);
	if (function)
		ft_putstr_fd(function, 2);
	ft_putendl_fd(err_msg, 2);
	return (0);
}

/**
 * @brief Close standard file descriptors and with the one provided.
 * 
 * @param root cmd struct containing the file descriptor to close
 */
void	close_fds(t_cmd *root)
{
	close(0);
	close(1);
	close(2);
	close(root->open_fd);
}

/**
 * Compares the lengths of the provided variable and environment variable.
 * The function returns the length of the longer of the two.
 *
 * @param lvar_s: The length of the provided variable.
 * @param env_var: The environment variable string in the format "KEY=VALUE".
 *
 * @return: The length of the longer of the two strings (either lvar_s or the
 * length before '=' in env_var).
 */
int	longer(int lvar_s, char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	if (i > lvar_s)
		return (i);
	else
		return (lvar_s);
}
