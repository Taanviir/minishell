/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/08/14 17:12:06 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test/test.h"
#include "minishell.h"

int	g_exit_status;

static char	*get_dir(t_env *env_list)
{
	char	*dir;
	char	*last;
	char	*temp;

	dir = get_env(env_list, "PWD");
	if (!ft_strncmp(dir, get_env(env_list, "HOME"), ft_strlen(dir)))
		dir = ft_strdup("[~]");
	else
	{
		last = ft_strrchr(dir, '/');
		if (last + 1)
		{
			temp = ft_bigjoin(3, "[", last + 1, "]");
			dir = temp;
		}
	}
	return (dir);
}

#ifdef TEST
t_cmd	*get_cmd(char *line, t_env **env_list)
{
	t_cmd	*root;
	char	*dir;
	char	*prompt;

	dir = get_dir(*env_list);
	prompt = ft_bigjoin(3, MAGENTA_B "ghost@shell:" BLUE, dir, " → " WHITE);
	line = readline(prompt);
	free(prompt);
	free(dir);
	if (!line)
		return (ft_exit(NULL, 0, env_list), NULL);
	add_history(line);
	root = parsecmd(line, env_list);
	test(root);
	return (root);
}
#else

t_cmd	*get_cmd(char *line, t_env **env_list)
{
	char	*dir;
	char	*prompt;
	t_cmd	*root;

	dir = get_dir(*env_list);
	prompt = ft_bigjoin(3, MAGENTA_B "ghost@shell:" BLUE, dir, " → " WHITE);
	// write(2, prompt, ft_strlen(prompt));
	// rl_already_prompted = 1;
	line = readline(prompt);
	free(prompt);
	free(dir);
	if (!line)
		return (ft_exit(NULL, 0, env_list), NULL);
	add_history(line);
	root = parsecmd(line, env_list);
	return (root);
}
#endif

int	main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char	*line;
	t_env	*env_list;

	if (argc != 1)
		return (printf(RED_B "Error: %s\n" WHITE, strerror(E2BIG)), ERR_ARGS);
	g_exit_status = 0;
	receive_signal();
	environment_init(&env_list, envp);
	while (true)
	{
		line = NULL;
		free_tree(runcmd(get_cmd(line, &env_list), &env_list));
		//TODO add line to _ VAR
		free(line);
	}
	free_list(env_list);
	// rl_clear_history();
	return (EXIT_SUCCESS);
}
