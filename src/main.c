/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/25 23:56:22 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../test/test.h"

#ifdef TEST
t_cmd	*get_cmd(char **envp)
{
	t_cmd	*root;
	char	*line;

	line = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!line || !*line)
		return (0);
	add_history(line);
	root = parsecmd(line, envp);
	test(root);
	free(line);
	return (root);
}
#else
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
#endif

int	main(int argc , char **argv __attribute__((unused)), char **envp)
{
	if (argc != 1)
	{
		printf(RED_B"Error: %s\n"WHITE, strerror(E2BIG));
		return (ERR_ARGS);
	}
	// receive_signal();
	// minishell loop
	while (1)
		runcmd(get_cmd(envp), envp);
	return (EXIT_SUCCESS);
}
