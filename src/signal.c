/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:55:49 by tanas             #+#    #+#             */
/*   Updated: 2023/10/07 16:40:53 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief signal handler for parent process
 * 
 * @param signum received signal
 */
void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130 << 8;
	}
}

/**
 * @brief signal handler for child process
 * 
 * @param signum received signal
 */
void	signal_handler_child(int signum)
{
	int	status;

	waitpid(-1, &status, 0);
	if (!WIFEXITED(status) && signum == SIGINT)
	{
		ft_putendl_fd("", 1);
		g_exit_status = 130 << 8;
	}
	else if (!WIFEXITED(status) && signum == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", 1);
		g_exit_status = 131 << 8;
	}
}

/**
 * @brief signal handler for heredoc
 * 
 * @param signum received signal
 * @note 'rl_done' is a global variable from 'readline.h'
 */
void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		rl_done = 1;
		ioctl(0, TIOCSTI, "\0");
		ft_putstr_fd("\b\b\b  \n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = QUIT_HEREDOC;
	}
}

/**
 * @brief receive signals from parent process
 */
void	receive_signal(void)
{
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}
