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

static char	**dup_env(char **envp)
{
	char 	**env_copy;
	int		length;
	int		i;

	length = 0;
	while (envp[length])
		length++;
	env_copy = malloc((length + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = -1;
	while (++i < length)
		env_copy[i] = ft_strdup(envp[i]);
	env_copy[length] = NULL;
	return (env_copy);
}

static void	print_env_list(char **envp)
{
	int		i;
	int		j;
	char	**env_var;
	char	**env_copy;
	char	*temp;

	env_copy = dup_env(envp);
	i = -1;
	while (env_copy[++i])
	{
		j = i;
		while (env_copy[++j])
		{
			if (ft_strncmp(env_copy[i], env_copy[j], ft_strlen(env_copy[i])) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
		}
	}
	i = -1;
	while (env_copy[++i])
	{
		if (env_copy[i][0] == '_')
			continue ;
		env_var = ft_split(env_copy[i], '=');
		printf("declare -x %s=\"%s\"\n", env_var[0], env_var[1]);
		free_double_ptr((void **) env_var);
	}
	free_double_ptr((void **) env_copy);
}

int	ft_export(char **argv, char **envp)
{
	int	i;
	int	name_len;
	int	index;

	if (!argv[1])
		return (print_env_list(envp), 0);
	i = 0;
	while (argv[++i])
	{
		if (!ft_is_alpha(argv[i][0]) && argv[i][0] != '\"' && argv[i][0] != '\'')
		{
			printf("export: `%s': not a valid identifier\n", argv[i]);
			continue ;
		}
		name_len = 0;
		while (argv[i][name_len] && argv[i][name_len] != '=')
			name_len++;
		index = 0;
		while (envp[index] && ft_strncmp(argv[i], envp[index], name_len))
			index++;
		if (!envp[index]) //! this should not work; make envp into a linked list
			envp[index + 1] = NULL;
		envp[index] = argv[i];
	}
	return (0);
}
