/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:19:24 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 01:19:24 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief expands the tilde expression to the required path
 * 
 * @param arg argument to expand
 * @param env_list environment list
 * @return 1 if the expansion was successful, 0 otherwise
 */
static int	handle_tilde(char *arg, t_env *env_list)
{
	if (!ft_strncmp("~+", arg, get_len("~+", arg)))
		return (ft_putstr_fd(get_env(env_list, "PWD")->value, 1), 1);
	else if (!ft_strncmp("~", arg, get_len("~", arg)))
		return (ft_putstr_fd(get_env(env_list, "HOME")->value, 1), 1);
	return (0);
}

/**
 * @brief process the flags of the echo command
 * 
 * @param argv arguments of the echo command
 * @param i index of the current argument
 * @param show_newline flag to show the newline
 * @return true if the flag was processed, false otherwise
 */
static bool	process_flags(char **argv, int *i, bool *show_newline)
{
	int	j;

	j = 1;
	while (argv[*i][j] && argv[*i][j] == 'n')
		j++;
	if (argv[*i][j] && argv[*i][j] != 'n')
	{
		if (*show_newline)
			*show_newline = true;
		return (false);
	}
	else if (!argv[*i][j])
	{
		(*i)++;
		*show_newline = false;
		return (true);
	}
	(*i)++;
	return (true);
}

/**
 * @brief builtin echo command
 * 
 * @param argc count of arguments
 * @param argv arguments
 * @param env_list environment list
 * @return status code
 */
int	ft_echo(int argc, char **argv, t_env *env_list)
{
	bool	show_newline;
	int		i;

	show_newline = true;
	i = 1;
	while (i < argc && !ft_strncmp("-n", argv[i], 2))
		if (!process_flags(argv, &i, &show_newline))
			break ;
	while (i < argc)
	{
		if (!handle_tilde(argv[i], env_list))
			ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (show_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
