/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/19 10:33:58 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	get input
	parse input
	execute
	free
	exit
*/
t_cmd	*get_cmd(char **envp)
{
	t_cmd	*root;
	char	*line;

	line = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!line || !*line)
		return (0);
	add_history(line);
	root = parsecmd(line, envp);
	return (root);
}

int	main(int argc , char **argv __attribute__((unused)), char **envp)
{
	t_cmd	*root;

	if (argc != 1)
	{
		printf(RED_B"Error: %s\n"WHITE, strerror(E2BIG));
		return (ERR_ARGS);
	}
	// receive_signal();
	// minishell loop
	while (1)
	{
		root = get_cmd(envp);
		printf("%i\n", root->type);
	}
	return (EXIT_SUCCESS);
}
