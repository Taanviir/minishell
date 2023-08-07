/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:54:03 by tanas             #+#    #+#             */
/*   Updated: 2023/08/07 15:29:20 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_and_export(char **argv, t_env **env, char *old_path)
{
	char	*path;

	path = getcwd(NULL, 0);
	argv[0] = "export";
	argv[1] = ft_strjoin("OLDPWD=", old_path);
	argv[2] = ft_strjoin("PWD=", path);
	ft_export(argv, NULL, env);
	free(argv[1]);
	free(argv[2]);
	free(old_path);
	free(path);
}

int	ft_cd(char **argv, t_env **env)
{
	char	*path;
	char	*old_path;

	if (argv[2])
		return (printf("minishell: cd: too many arguments\n"), 1);
	if (!argv[1] || argv[1][0] == '~')
		path = getenv("HOME");
	else if (!ft_strncmp(argv[1], "-", 1))
	{
		path = getenv("OLDPWD");
		if (!path)
			return (printf("minishell: cd: OLDPWD not set\n"), 2);
		printf("%s\n", path);
	}
	else
		path = argv[1];
	old_path = getcwd(NULL, 0);
	if (chdir(path) == 0)
		set_and_export(argv, env, old_path);
	else
	{
		free(old_path);
		return (printf("cd: no such file or directory: %s\n", path), 3);
	}
	return (0);
}
