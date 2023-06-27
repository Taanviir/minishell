/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/06/21 15:09:54 by sabdelra         ###   ########.fr       */
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

void	get_cmd(void)
{
	char	*line;

	line = readline(MAGENTA_B"ghost@shell → "WHITE);
	if (!line || !*line)
		return ;
	quote_check(line);
	add_history(line);
	free(line);
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
	if (argc != 1)
	{
		printf(RED_B"Error: %s\n"WHITE, strerror(E2BIG));
		return (ERR_ARGS);
	}
	// receive_signal();
	// minishell loop
	while (1)
	{
		get_cmd();
	/* free whatever needs to be freed */
	}
	return (EXIT_SUCCESS);

}