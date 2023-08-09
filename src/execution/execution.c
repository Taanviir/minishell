/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/08/09 12:03:35 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO maybe doesn't belong here, maybe libft or a more global file
int	get_len(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	return (ft_strlen(str2));
}

// TODO do something about this function it looks bad lol can be moved to execute command
int	execute_builtin(char **argv, char **envp, t_env **env)
{
	if (!ft_strncmp(argv[0], "echo", get_len(argv[0], "echo")))
		return (ft_echo(argv), 1);
	if (!ft_strncmp(argv[0], "cd", get_len(argv[0], "cd")))
		return (ft_cd(argv, env), 1);
	else if (!ft_strncmp(argv[0], "pwd", get_len(argv[0], "pwd")))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(argv[0], "export", get_len(argv[0], "export")))
		return (ft_export(argv, envp, env), 1);
	else if (!ft_strncmp(argv[0], "unset", get_len(argv[0], "unset")))
		return (ft_unset(argv, env), 1);
	else if (!ft_strncmp(argv[0], "env", get_len(argv[0], "env")))
		return (ft_env(argv, env), 1);
	else if (!ft_strncmp(argv[0], "exit", get_len(argv[0], "exit"))) {
		// TODO shit's weird homie, can't exit mid program
		free_tree(cmd);
    return (ft_exit(EXIT_SUCCESS, env), 1);
  }
	return (0);
}

//! handle printf &
static void	execute_bgcmd(t_cmd *cmd, char **envp, t_env **env)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	if (!fork())
	{
		runcmd(bgcmd->cmd, envp, env);
		free_tree(cmd);
		exit(0);
	}
	wait(0);
}

static void	execute_seq(t_cmd *cmd, char **envp, t_env **env)
{
	t_seqcmd	*seqcmd;

	seqcmd = (t_seqcmd *)cmd;
	if (!fork())
	{
		runcmd(seqcmd->left, envp, env);
		free_tree(cmd);
		exit(0);
	}
	wait(NULL);
	runcmd(seqcmd->right, envp, env);
}

typedef void (*t_execute)(t_cmd *cmd, char **envp, t_env **env);

t_cmd *runcmd(t_cmd *cmd, char **envp, t_env **env)
{
	t_execute	executers[5];

	executers[0] = execute_cmd;
	executers[1] = execute_redir;
	executers[2] = execute_pipe;
	executers[3] = execute_seq;
	executers[4] = execute_bgcmd;
	if (!cmd)
		return (NULL);
	executers[cmd->type](cmd, envp, env);
	return(cmd);
}
