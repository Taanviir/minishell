/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:36:36 by tanas             #+#    #+#             */
/*   Updated: 2023/10/08 17:36:36 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the current working directory.
 * 
 * @param env_list environment list 
 * @return current working directory
 */
static char	*get_dir(t_env *env_list)
{
	char	*dir;
	char	*home;
	char	*last;
	char	*result;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (ft_strdup("[.]"));
	home = get_env_value(env_list, "HOME");
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

/**
 * @brief Get the command from the user.
 * 
 * @param line user input
 * @param env_list environment list
 * @return command
 */
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
