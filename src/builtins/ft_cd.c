/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:36:13 by tanas             #+#    #+#             */
/*   Updated: 2023/10/08 17:36:13 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief updates env_list with new PWD and OLDPWD
 * 
 * @param env_list env_list to update
 * @param old_path old path to update OLDPWD
 */
static void	update_env(t_env **env_list, char *old_path)
{
	char	**argv;
	char	*line;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (old_path)
		line = ft_bigjoin(4, "export OLDPWD=", old_path, " PWD=", cwd);
	else
		line = ft_bigjoin(2, "export OLDPWD= PWD=", cwd);
	argv = ft_split(line, ' ');
	ft_export(argv, env_list);
	free_double_ptr((void **) argv);
	free(line);
	free(cwd);
}

/**
 * @brief expands ~ to HOME
 * 
 * @param path path to expand
 * @param env_list env_list to get HOME from
 * @return 1 if error, 0 if success
 */
static int	expand_tilde(char **path, t_env **env_list)
{
	char	*home;
	char	*expanded_path;

	home = get_env_value(*env_list, "HOME");
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

/**
 * @brief changes directory
 * 
 * @param env_list env_list to update
 * @param path path to change to
 * @param old_path old path to update OLDPWD
 * @return 1 if error, 0 if success
 */
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
	return (1);
}

/**
 * @brief changes directory
 * 
 * @param argv arguments
 * @param env_list env_list to update
 * @return 1 if error, 0 if success
 */
int	ft_cd(char **argv, t_env **env_list)
{
	char	*path;
	char	*old_path;

	if (!argv[1] || !ft_strncmp(argv[1], "~", get_len(argv[1], "~")))
	{
		path = get_env_value(*env_list, "HOME");
		if (!path)
			return (printf("minishell: cd: HOME not set\n"), 1);
	}
	else if (!ft_strncmp(argv[1], "-", 1))
	{
		path = get_env_value(*env_list, "OLDPWD");
		if (!path)
			return (printf("minishell: cd: OLDPWD not set\n"), 1);
	}
	else
		path = argv[1];
	if (expand_tilde(&path, env_list))
		return (1);
	old_path = getcwd(NULL, 0);
	if (change_path(env_list, path, old_path))
		return (1);
	free(old_path);
	return (0);
}
