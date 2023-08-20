/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:55:49 by tanas             #+#    #+#             */
/*   Updated: 2023/08/20 18:27:22 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
		printf("\n");
}

void	receive_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
