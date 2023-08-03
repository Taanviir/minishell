/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:47:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/03 17:47:30 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_env_list(char **envp)
// {
// 	int		i;
// 	int		j;
// 	char	**env_var;
// 	char	*temp;

// 	i = -1;
// 	while (envp[++i])
// 	{
// 		j = i;
// 		while (envp[++j])
// 		{
// 			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
// 			{
// 				temp = envp[i];
// 				envp[i] = envp[j];
// 				envp[j] = temp;
// 			}
// 		}
// 	}
// 	i = -1;
// 	while (envp[++i])
// 	{
// 		if (envp[i][0] == '_')
// 			continue ;
// 		env_var = ft_split(envp[i], '=');
// 		printf("declare -x %s=\"%s\"\n", env_var[0], env_var[1]);
// 		free_double_ptr((void **) env_var);
// 	}
// }

// int	ft_export(char **argv, char **envp)
// {
// 	int		i;
// 	int		name_len;
// 	int		index;

// 	if (!argv[1])
// 		return (print_env_list(envp), 0);
// 	i = 0;
// 	while (argv[++i])
// 	{
// 		if (!ft_is_alpha(argv[i][0]) && argv[i][0] != '\"' && argv[i][0] != '\'')
// 		{
// 			printf("export: `%s': not a valid identifier\n", argv[i]);
// 			continue ;
// 		}
// 		name_len = 0;
// 		while (argv[i][name_len] && argv[i][name_len] != '=')
// 			name_len++;
// 		index = 0;
// 		while (envp[index] && ft_strncmp(argv[i], envp[index], name_len))
// 			index++;
// 		if (!envp[index])
// 			envp[index + 1] = NULL;
// 		envp[index] = argv[i];
// 	}
// 	return (0);
// }
