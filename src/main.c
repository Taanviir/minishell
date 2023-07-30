/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/31 00:52:27 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../test/test.h"

t_signal	g_signal;

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
	char	*dir;
	char	*prompt;
	t_cmd	*root;

	dir = getcwd(NULL, 0);
	prompt = ft_bigjoin(6, MAGENTA_B, "ghost@shell:", BLUE, dir, " → ", WHITE);
	line = readline(prompt);
	if (!line || !*line)
		return (NULL);
	free(prompt);
	free(dir);
	add_history(line);
	root = parsecmd(line, envp);
	return (root);
}
#endif

int	main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char	*line;

	if (argc != 1)
		return (printf(RED_B"Error: %s\n"WHITE, strerror(E2BIG)), ERR_ARGS);
	receive_signal();
	while (g_signal.exit_status == 0)
	{
		line = NULL;
		runcmd(get_cmd(envp, line), envp);
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
