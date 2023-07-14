/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/14 04:05:55 sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
void	quote_check(char *line)
{
	int i = -1;
	int counter = 0;
	// while (line[++i] && !(line[i] == '\'' && line[i - 1] != '\\'))
	while (line[++i]) // || ft_strchr("'", line[i]))
		if (line[i] == '"' || line[i] == '\'')
			counter++;
	if ((counter % 2) == 1)
		printf("quote error lmao\n");
}

t_cmd	*get_cmd(char **envp)
{
	char	*line;
	t_cmd	*root;

	line = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!line || !*line)
		return (0);
	quote_check(line);
	add_history(line);
	root = parsecmd(line, envp);
	return (root);
}

/*
	get input
	parse input
	execute
	free
	exit
*/
#ifdef TEST
int	main(int argc , char **argv __attribute__((unused)), char **envp)
{
	// char png[10];
	if (argc != 1)
	{
		printf(RED_B"Error: %s\n"WHITE, strerror(E2BIG));
		return (ERR_ARGS);
	}
	// receive_signal();
	// minishell loop
	while (1)
	{
		print(get_cmd(envp));
		// free(line);
	}
	return (EXIT_SUCCESS);
}
#else
#define WHATEVERNEEDSTOBEFREEED line
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
	{
		get_cmd(envp); // execute(get_cmd(envp)) when we got execute
		// free(WHATEVERNEEDSTOBEFREEED);
	/* free whatever needs to be freed */
	}
	return (EXIT_SUCCESS);
}
#endif
