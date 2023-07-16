/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/13 22:33:06 by tanas            ###   ########.fr       */
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
int	main(int argc , char **argv __attribute__((unused)), char **envp __attribute__((unused)))
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
