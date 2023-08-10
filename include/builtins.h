/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:00:27 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/10 18:42:32 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// UTILS
int		name_len(char *arg);
bool	check_char(char c, char *argv);

// BUILTINS
int		ft_pwd(void);
int		ft_echo(char **argv);
int		ft_env(char **argv, t_env **env_list);
int		ft_cd(char **argv, t_env **env_list);
int		ft_exit(int err_num, t_env **env_list);
int		ft_unset(char **argv, t_env **env_list);
int		ft_export(char **argv, t_env **env_list);

#endif
