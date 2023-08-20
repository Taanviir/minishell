/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:54:03 by tanas             #+#    #+#             */
/*   Updated: 2023/08/20 21:18:05 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO handle unset HOME
// static void get_home(t_env *env_list) {
// 	char *home;

// 	// we attempt get_env
// 	// if env is unset
// 	// iterate over all directories in /Users
// 	// the one that doesn't error we set as home

// }
static void	update_env(t_env **env_list, char *old_path)
{
	char	**argv;
	char	*line;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	line = ft_bigjoin(5, "export ", "OLDPWD=", old_path, " PWD=", cwd);
	argv = ft_split(line, ' ');
	ft_export(argv, env_list);
	free_double_ptr((void **) argv);
	free(line);
	free(cwd);
}

static int	expand_tilde(char **path, t_env **env_list)
{
	char	*home;
	char	*expanded_path;

	home = get_env(*env_list, "HOME");
	if (!home)
		return (printf("minishell: cd: HOME not set\n"), 1);
	if ((*path)[0] == '~')
	{
		expanded_path = NULL;
		expanded_path = ft_bigjoin(3, expanded_path, home, *path + 1);
		*path = expanded_path;
	}
	return (0);
}

static int	change_path(t_env **env_list, char *path, char *old_path)
{
	DIR	*directory;

	directory = opendir(path);
	if (!directory)
		return (perror("minishell: cd"), 1);
	closedir(directory);
	if (!chdir(path))
	{
		if (!ft_strncmp(path, "OLDPWD", 6))
			printf("%s\n", path);
		update_env(env_list, old_path);
		return (0);
	}
	printf("minishell: cd: %s: %s\n", path, strerror(ENOENT));
	return (1);
}

int	ft_cd(char **argv, t_env **env_list)
{
	char	*path;
	char	*old_path;

	if (!ft_strncmp(argv[1], "~", get_len(argv[1], "~")))
	{
		path = get_env(*env_list, "HOME");
		if (!path)
			return (printf("minishell: cd: HOME not set\n"), 1);
	}
	else if (!ft_strncmp(argv[1], "-", 1))
	{
		path = get_env(*env_list, "OLDPWD");
		if (!path)
			return (printf("minishell: cd: OLDPWD not set\n"), 1);
	}
	else
		path = argv[1];
	if (expand_tilde(&path, env_list))
		return (1);
	old_path = get_env(*env_list, "PWD");
	if (change_path(env_list, path, old_path))
		return (1);
	return (0);
}
