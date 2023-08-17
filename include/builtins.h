/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:00:27 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/17 18:10:36 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenizer.h"

#ifndef BUILTINS_H
# define BUILTINS_H

// UTILS
int		name_len(char *arg);
bool	check_char(char c, char *argv);

// BUILTINS
int		ft_pwd(t_env *env_list);
int		ft_echo(t_exec *cmd);
int		ft_env(char **argv, t_env **env_list);
int		ft_cd(int argc, char **argv, t_env **env_list);
int		ft_exit(t_cmd *cmd, t_env **env_list);
int		ft_unset(char **argv, t_env **env_list);
int		ft_export(char **argv, t_env **env_list);

#endif
