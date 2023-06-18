/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:55:49 by tanas             #+#    #+#             */
/*   Updated: 2023/06/15 19:32:30 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

In interactive mode:
◦ ctrl-C displays a new prompt on a new line. -> SIGINT
◦ ctrl-D exits the shell. -> EOF basically
◦ ctrl-\ does nothing. -> SIGQUIT
*/

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("SIGINT received\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
	}
	else if (signum == SIGQUIT)
		return ;
}

void	receive_signal(void)
{
	struct sigaction	action;

	action.sa_handler = signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}