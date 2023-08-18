/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:54:03 by tanas             #+#    #+#             */
/*   Updated: 2023/08/17 18:51:25 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_env **env_list, char *old_path)
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

int	change_path(t_env **env_list, char *path, char *old_path)
{
	DIR	*directory;

	directory = opendir(path);
	if (directory)
	{
		closedir(directory);
		printf("minishell: cd: %s: %s\n", path, strerror(EACCES));
		return (1);
	}
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

int	ft_cd(int argc, char **argv, t_env **env_list)
{
	char	*path;
	char	*old_path;

	if (argc > 2)
		return (printf("minishell: cd: too many arguments\n"), 1);
	if (argc == 1 || !ft_strncmp(argv[1], "~", 1))
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
	old_path = get_env(*env_list, "PWD");
	if (change_path(env_list, path, old_path))
		return (1);
	return (0);
}
