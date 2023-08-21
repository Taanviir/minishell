/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:20:16 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 01:20:16 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	check_digit(bool is_negative, long result, int digit)
{
	if ((!is_negative && (result > (LONG_MAX - digit) / 10))
		|| (is_negative && (-result < (LONG_MIN + digit) / 10)))
	{
		if (is_negative)
			return (LONG_MIN);
		return (LONG_MAX);
	}
	return (0);
}

static long	ft_strtol(const char *str, char **endptr)
{
	long	result;
	bool	is_negative;
	int		digit;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	is_negative = (*str == '-');
	if (*str == '-' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (check_digit(is_negative, result, digit))
		{
			if (endptr)
				*endptr = (char *)str;
			return (check_digit(is_negative, result, digit));
		}
		result = result * 10 + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	if (is_negative)
		return (-result);
	return (result);
}

static int	exit_check(t_exec *exec)
{
	int		i;
	char	*endptr;
	long	num;

	i = 0;
	while (exec->argv && exec->argv[++i])
	{
		num = ft_strtol(exec->argv[i], &endptr);
		if (*endptr != '\0' || (num == LONG_MIN || num == LONG_MAX))
			return (print_error("numeric argument required", "exit: "), 255);
	}
	if (exec->argc == 2 && ft_strncmp(exec->argv[1], "255", 3) > 0)
	{
		num = ft_strtol(exec->argv[1], NULL);
		return ((int)(num % 256));
	}
	else if (exec->argc == 2)
		return ((int) ft_strtol(exec->argv[1], NULL));
	return (0);
}

int	ft_exit(t_cmd *cmd, t_env **env_list)
{
	t_exec	*exec;

	if (cmd)
	{
		exec = (t_exec *) cmd;
		if (exec->argc > 2)
			return (printf("minishell: exit: too many arguments\n"), 1);
		g_exit_status = exit_check((t_exec *) cmd);
	}
	free_tree(cmd);
	free_list(*env_list);
	printf("exit\n");
	exit(g_exit_status);
}
