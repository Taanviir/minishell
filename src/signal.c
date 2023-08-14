/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:55:49 by tanas             #+#    #+#             */
/*   Updated: 2023/08/14 13:36:45 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* In interactive mode:
* ctrl-C displays a new prompt on a new line. -> SIGINT
* ctrl-\ does nothing. -> SIGQUIT

* when in command:
* ctrl-C interrupts the process and in heredoc it stops then returns a num. -> SIGINT
* ctrl-\ quits the process, prints Quit; {} and in heredoc it does nothing. -> SIGQUIT
* ctrl-D just stops the process and returns 0. -> EOF
*/

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

void	receive_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
