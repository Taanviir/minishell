/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 16:27:19 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../test/test.h"

#ifdef TEST
t_cmd	*get_cmd(char **envp, char *line)
{
	t_cmd	*root;

	line = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!line || !*line)
		return (free(line), NULL);
	add_history(line);
	// char	line[] = "echo 'hello'";
	root = parsecmd(line, envp);
	test(root);
	return (root);
}
#else
t_cmd	*get_cmd(char **envp, char *line)
{
	t_cmd	*root;

	line = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!line || !*line)
		return (free(line), NULL);
	add_history(line);
	root = parsecmd(line, envp);
	return (root);
}
#endif

int	main(int argc , char **argv __attribute__((unused)), char **envp)
{
	if (argc != 1)
		return (printf(RED_B"Error: %s\n"WHITE, strerror(E2BIG)), ERR_ARGS);
	char *line;
	// receive_signal();
	// minishell loop
	while (1) {
		line = NULL;
		runcmd(get_cmd(envp, line), envp);
		free(line);
	}
	return (EXIT_SUCCESS);
}
