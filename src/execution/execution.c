/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/08/07 15:22:21 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_fp(char *program_name) {
	char *fp;
	char **path;
	int i;

	path = ft_split(getenv("PATH"), ':');
	fp = NULL;
	i = -1;
	while (path[++i])
	{
		fp = ft_bigjoin(3, path[i], "/", program_name);
		if (!access(fp, X_OK))
			break;
		else
		{
			free(fp);
			fp = NULL;
		}
	}
	free_double_ptr((void **)path);
	return (fp);
}

int	length(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	return (ft_strlen(str2));
}

static int	execute_builtin(t_exec *cmd, char **envp, t_env **env)
{
	if (!ft_strncmp(cmd->argv[0], "echo", length(cmd->argv[0], "echo")))
		return (ft_echo(cmd->argv), 0);
	if (!ft_strncmp(cmd->argv[0], "cd", length(cmd->argv[0], "cd")))
		return (ft_cd(cmd->argv, env), 0);
	else if (!ft_strncmp(cmd->argv[0], "pwd", length(cmd->argv[0], "pwd")))
		return (ft_pwd(), 0);
	else if (!ft_strncmp(cmd->argv[0], "export", length(cmd->argv[0], "export")))
		return (ft_export(cmd->argv, envp, env), 0);
	else if (!ft_strncmp(cmd->argv[0], "unset", length(cmd->argv[0], "unset")))
		return (ft_unset(cmd->argv, env), 0);
	else if (!ft_strncmp(cmd->argv[0], "env", length(cmd->argv[0], "env")))
		return (ft_env(cmd->argv, env), 0);
	else if (!ft_strncmp(cmd->argv[0], "exit", length(cmd->argv[0], "exit")))
		return (ft_exit(EXIT_SUCCESS), 0);
	return (1);
}

static void	execute_cmd(t_cmd *cmd, char **envp, t_env **env)
{
	t_exec	*execcmd;
	char	*fp;

	execcmd = (t_exec *)cmd;
	if (!execcmd->argv[0])
		return ;
	if (!execute_builtin(execcmd, envp, env))
		return ;
	fp = get_fp(execcmd->argv[0]);
	if (!fp)
	{
		printf("%s: command not found\n", fp);
		return ;
	}
	if (!fork())
	{
		execve(fp, execcmd->argv, envp);
		free(fp);
	}
	wait(0);
	free(fp);
}

static void execute_redir(t_cmd *cmd, char **envp, t_env **env)
{
	t_redircmd	*redircmd;
	int			new_fd;

	redircmd = (t_redircmd *)cmd;
	new_fd = open(redircmd->fp, redircmd->mode, S_IRWXU);
	if (new_fd < 0)
		write(2, "file not found\n", 2);
	dup2(new_fd, redircmd->fd);
	runcmd(redircmd->cmd, envp, env);
	close(new_fd);
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
		exit(0);
	} else if (!fork()) {
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		runcmd(pipecmd->right, envp, env);
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
		exit(0);
	}
	wait(NULL);
	runcmd(seqcmd->right, envp, env);
}

typedef void (*t_execute)(t_cmd *cmd, char **envp, t_env **env);

void runcmd(t_cmd *cmd, char **envp, t_env **env)
{
	t_execute executers[5];

	executers[0] = execute_cmd;
	executers[1] = execute_redir;
	executers[2] = execute_pipe;
	executers[3] = execute_seq;
	executers[4] = execute_bgcmd;
	if (!cmd)
		return;
	executers[cmd->type](cmd, envp, env);
}
