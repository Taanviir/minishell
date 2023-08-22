/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/08/23 02:59:57 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_dir(t_env *env_list)
{
	char	*dir;
	char	*home;
	char	*last;
	char	*result;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (ft_strdup("[.]"));
	home = get_env(env_list, "HOME");
	if (home && !ft_strncmp(dir, home, get_len(dir, home)))
		result = ft_strdup("[~]");
	else if (dir[0] == '/' && !dir[1])
		result = ft_strdup("[/]");
	else
	{
		last = ft_strrchr(dir, '/');
		if (last)
			result = ft_bigjoin(3, "[", last + 1, "]");
		else
			result = dir;
	}
	free(dir);
	return (result);
}

t_cmd	*get_cmd(char *line, t_env **env_list)
{
	char	*dir;
	char	*prompt;
	t_cmd	*root;

	dir = get_dir(*env_list);
	prompt = ft_bigjoin(3, MAGENTA_B "ghost@shell:" BLUE, dir, " → " WHITE);
	line = readline(prompt);
	free(prompt);
	free(dir);
	if (!line)
		return (ft_exit(NULL, env_list), NULL);
	add_history(line);
	root = parsecmd(line, env_list);
	return (root);
}

//TODO add line to _ VAR
int	main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char	*line;
	t_env	*env_list;
	t_cmd	*root;

	if (argc != 1)
		return (printf(RED_B "Error: %s\n" WHITE, strerror(E2BIG)), ERR_ARGS);
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
	free_list(env_list);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
