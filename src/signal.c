/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:55:49 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 14:04:25 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	signal_handler_child(int signum)
{
	int status;

	if (signum == SIGINT)
		printf("\n");
	else if (signum == SIGQUIT)
		printf("Quit: 3\n");
	waitpid(-1, &status, 0);
	if (!WIFEXITED(status) && signum == SIGINT)
		g_exit_status = 130 << 8;
	else if (!WIFEXITED(status) && signum == SIGINT)
		g_exit_status = 131 << 8;
}

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		rl_done = 1;
		ft_putstr_fd("press enter", 2);
		// ioctl(0, TIOCSTI, "\n");
		g_exit_status = QUIT_HEREDOC;
	}
}

void	receive_signal(void)
{
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}
