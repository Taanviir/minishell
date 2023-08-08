/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/08/08 05:26:17 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	return (ft_strlen(str2));
}

//! flipped the logic here since it makes more sense to say if(execute_builtin) return, instead of !
//! maybe also change it to bool since its a binary yes or no
int	execute_builtin(t_cmd *cmd, char **envp, t_env **env)
{
	t_exec	*exec;

	exec = (t_exec *)cmd;
	if (!ft_strncmp(exec->argv[0], "echo", length(exec->argv[0], "echo")))
		return (ft_echo(exec->argv), 1);
	if (!ft_strncmp(exec->argv[0], "cd", length(exec->argv[0], "cd")))
		return (ft_cd(exec->argv, env), 1);
	else if (!ft_strncmp(exec->argv[0], "pwd", length(exec->argv[0], "pwd")))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(exec->argv[0], "export", length(exec->argv[0], "export")))
		return (ft_export(exec->argv, envp, env), 1);
	else if (!ft_strncmp(exec->argv[0], "unset", length(exec->argv[0], "unset")))
		return (ft_unset(exec->argv, env), 1);
	else if (!ft_strncmp(exec->argv[0], "env", length(exec->argv[0], "env")))
		return (ft_env(exec->argv, env), 1);
	else if (!ft_strncmp(exec->argv[0], "exit", length(exec->argv[0], "exit"))){
		//! shit's weird homie, can't exit mid program
		free_tree(cmd);
		return (ft_exit(EXIT_SUCCESS), 1);
	}
	return (0);
}

// the here-doc case does this one completely different
static void execute_redir(t_cmd *cmd, char **envp, t_env **env) {
  t_redircmd *redircmd;
  int new_fd;
  int save_fd;

  redircmd = (t_redircmd *)cmd;
  save_fd = dup(redircmd->fd); // saving previous std in/out
  if (!redircmd->here_doc) //! normal redirection
    new_fd = open(redircmd->fp, redircmd->mode, S_IRWXU);
  else
    new_fd = redircmd->here_doc;
  if (new_fd < 0)
    write(2, "file not found\n", 2);
  dup2(new_fd, redircmd->fd); // replacing cmd->fd with the new fd (read pipe file/pipe, or write file/pipe)
  close(new_fd);
  runcmd(redircmd->cmd, envp, env);
  dup2(save_fd, redircmd->fd);
  close(save_fd);
}

static void execute_pipe(t_cmd *cmd, char **envp, t_env **env)
{
	t_pipecmd	*pipecmd;
	int			p[2];

	pipecmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
		write(2, "failed to pipe\n", 16);
	if (!fork()) {
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		runcmd(pipecmd->left, envp, env);
		free_tree(cmd);
		exit(0);
	} else if (!fork()) {
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		runcmd(pipecmd->right, envp, env);
		free_tree(cmd);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

//! handle printf &
static void execute_bgcmd(t_cmd *cmd, char **envp, t_env **env)
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

static void execute_seq(t_cmd *cmd, char **envp, t_env **env)
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
	t_execute executers[5];

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
