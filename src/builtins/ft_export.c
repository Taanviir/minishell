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

//instead of sorting hte linked list, sort envp
static void	sort_envp(char **envp)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
	{
		j = i;
		while (envp[++j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
		}
	}
}

static void	print_env_list(char **envp)
{
	t_env	*env;
	t_env	*temp;

	sort_envp(envp);
	environment_init(&env, envp);
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, "_", 1) != 0)
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
		if (temp == env)
			break ;
	}
	free_env_list(&env);
}

int	name_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

bool	is_name(char c, char *argv)
{
	if (!ft_is_alpha(c) && c != '\"' && c != '\'')
	{
		printf("export: `%s': not a valid identifier\n", argv);
		return (true);
	}
	return (false);
}

//! needs testing
int	ft_export(char **argv, char **envp, t_env **env)
{
	int		i;
	t_env	*temp;

	if (!argv[1])
		return (print_env_list(envp), 1);
	i = 0;
	while (argv[++i])
	{
		i += is_name(argv[i][0], argv[i]);
		temp = *env;
		while (temp->next != *env)
		{
			if (!ft_strncmp(argv[i], temp->name, name_len(argv[i])))
			{
				free(temp->value);
				temp->value = ft_strdup(argv[i] + name_len(argv[i]) + 1);
				break ;
			}
			temp = temp->next;
		}
		if (temp->next == *env)
			add_node_bottom(env, argv[i]);
		printf("%s\n", temp->next->name);
	}
	return (0);
}
