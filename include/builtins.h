/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:00:27 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/24 10:08:12 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "tokenizer.h"

// UTILS
int		name_len(char *arg);
int		_name(char *var1, char *var2);
bool	check_var_export(char *arg, int *ret);
bool	check_var_unset(char *arg);
void	print_env_list(t_env **env_list);

// BUILTINS
int		ft_pwd(void);
int		ft_echo(int argc, char **argv, t_env *env_list);
int		ft_env(char **argv, t_env **env_list);
int		ft_cd(char **argv, t_env **env_list);
int		ft_exit(t_cmd *cmd, t_env **env_list);
int		ft_unset(char **argv, t_env **env_list);
int		ft_export(char **argv, t_env **env_list);

#endif
