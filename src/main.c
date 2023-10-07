/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 02:59:57 by tanas             #+#    #+#             */
/*   Updated: 2023/10/07 16:43:25 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char	*line;
	t_env	*env_list;
	t_cmd	*root;

	if (argc != 1)
		return (printf(RED_B "Error: %s\n" WHITE, strerror(E2BIG)), 1);
	g_exit_status = 0;
	environment_init(&env_list, envp);
	while (true)
	{
		receive_signal();
		line = NULL;
		root = get_cmd(line, &env_list);
		free_tree(runcmd(root, &env_list, root));
		free(line);
	}
	return (EXIT_SUCCESS);
}
