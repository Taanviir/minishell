/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:55:49 by tanas             #+#    #+#             */
/*   Updated: 2023/08/19 19:48:34 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

// TODO if SIGINT in child then print \n and interrupt child
// TODO if SIGQUIT, print Quit: 3\n and exit code is 131
void	sigint_handler_child(int signum)
{
	(void) signum;
	int status;

	printf("\n");
	waitpid(-1, &status, 0);
	if (!WIFEXITED(status))
		g_exit_status = 130 << 8;
}

// TODO SIGINT just stops heredoc (prints \n)
// TODO SIGQUIT does nothing
// CTRL D does nothing 
void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
		return ;
	else if (signum == SIGQUIT)
		return ;
}

void	receive_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
