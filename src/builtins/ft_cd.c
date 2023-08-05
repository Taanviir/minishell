/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:54:03 by tanas             #+#    #+#             */
/*   Updated: 2023/08/05 14:51:55 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **argv, char **envp)
{
	char	*path;

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
	if (chdir(path) == -1)
		return (printf("minishell: cd: no such file or directory: %s\n", path), 3);
	//update $OLDPWD and $PWD
	argv[0] = "export";
	argv[1] = ft_strjoin("OLDPWD=", path);
	ft_export(argv, envp);
	free(argv[1]);
	// path = getcwd(NULL, 0);
	// argv[1] = ft_strjoin("PWD=", path);
	// free(argv[1]);
	// free(path);
	// ft_export(argv, envp);	
	//! OLDPWD needs to be unset when minishell is launched
	return (0);
}
