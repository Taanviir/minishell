/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <tanas@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/18 19:09:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//! this quote check is wrong it fails on "'
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

char	*get_cmd(void)
{
	char	*cmd;

	cmd = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!cmd || !*cmd)
		return (NULL);
	quote_check(cmd);
	add_history(cmd);
	return (cmd);
}

/*
	get input
	parse input
	execute
	free
	exit
*/
#ifdef TEST
#include <string.h>
t_cmd	*get_cmd(char **envp)
{
	t_cmd	*root;
	char	*line;

	line = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!line || !*line)
		return (0);
	quote_check(line);
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
	int	saved_stdout;
	int	fd;
	while (1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		root = get_cmd(envp);
		fd = open("./test.dot", O_WRONLY | O_CREAT | O_TRUNC);
		dup2(fd, STDOUT_FILENO);
		printf("digraph Trie {\n");
		print(root);
		printf("}\n");
		dup2(saved_stdout, 1);
	}
	return (EXIT_SUCCESS);
}
#else
#define WHATEVERNEEDSTOBEFREEED line
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
int	main(int argc , char **argv __attribute__((unused)), char **envp)
{
	char	*cmd;

	if (argc != 1)
	{
		printf(RED_B"Error: %s\n"WHITE, strerror(E2BIG));
		return (ERR_ARGS);
	}
	// receive_signal();
	// minishell loop
	while (1)
	{
		cmd = get_cmd();
		t_cmd *root = parsecmd(cmd, envp);
		printf("%i\n", root->type);
		free(cmd);
	/* free whatever needs to be freed */
	}
	return (EXIT_SUCCESS);
}
#endif
