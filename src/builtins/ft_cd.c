/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:54:03 by tanas             #+#    #+#             */
/*   Updated: 2023/08/03 19:57:27 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **argv)
{
	char	*path;

	if (argv[2])
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (!argv[1] || argv[1][0] == '~')
		path = getenv("HOME");
	else if (!ft_strncmp(argv[1], "-", 1))
	{
		path = getenv("OLDPWD");
		printf("%s\n", path);
	}
	else
		path = argv[1];
	if (chdir(path) != -1)
		return ;
	//update $OLDPWD
	printf("cd: no such file or directory: %s\n", path);
	// else
}
