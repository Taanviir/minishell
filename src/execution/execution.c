/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:07:04 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 14:37:06y sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_fp(char *program_name, char **envp)
{
	char	*fp;
	char	**path;
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	path = ft_split(*envp + 5, ':');
	fp = NULL;
	i = -1;
	while (path[++i])
	{
		fp = ft_strjoin(ft_strjoin(ft_strdup(path[i]), "/"), program_name);
		if (access(fp, X_OK) == F_OK)
			break ;
		else
		{
			free(fp);
			fp = NULL;
		}
	}
	free_double_ptr((void **) path);
	return (fp);
}

static void	execute_cmd(t_cmd	*cmd, char **envp)
{
	t_exec	*execcmd;
	char	*fp;

	execcmd = (t_exec *)cmd;
	if (!execcmd->argv[0])
		exit(EXIT_FAILURE);
	fp = get_fp(execcmd->argv[0], envp);
	if (!fp)
		ft_error("program not found", 1);
	if (!fork())
		execve(fp, execcmd->argv, envp);
	wait(0);
	free(fp);
}

static void	execute_redir(t_cmd *cmd, char **envp)
{
	t_redircmd	*redircmd;
	int			new_fd;

	redircmd = (t_redircmd *)cmd;
	new_fd = open(redircmd->fp, redircmd->mode);
	if (new_fd < 0)
		write(2, "\n", 2);
	dup2(new_fd, redircmd->fd);
	runcmd(redircmd->cmd, envp);
}

static void	execute_pipe(t_cmd *cmd, char **envp)
{
	t_pipecmd	*pipecmd;
	int			p[2];
	pid_t		pid[2];
	pipecmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
		write(2, "failed to pipe\n", 16);
	pid[0] = fork();
	if (!pid[0])
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		runcmd(pipecmd->left, envp);
		exit(0);
	}
	pid[1] = fork();
	if (!pid[1])
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		runcmd(pipecmd->right, envp);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

static void	execute_bgcmd(t_cmd *cmd, char **envp)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	if (!fork())
		runcmd(bgcmd->cmd, envp);
}

static void	execute_seq(t_cmd *cmd, char **envp)
{
	t_seqcmd	*seqcmd;

	seqcmd = (t_seqcmd *)cmd;
	if (!fork())
		runcmd(seqcmd->left, envp);
	wait(NULL);
	runcmd(seqcmd->right, envp);
}

typedef void(*t_execute)(t_cmd *cmd, char **envp);

void	runcmd(t_cmd *cmd, char **envp)
{
	t_execute	executers[5];

	executers[0] = execute_cmd;
	executers[1] = execute_redir;
	executers[2] = execute_pipe;
	executers[3] = execute_seq;
	executers[4] = execute_bgcmd;
	if (!cmd) // get_cmd returns null if empty line is returned from readline which triggers this condition
		return ;
	executers[cmd->type](cmd, envp);
}

// int main(int argc, char **argv, char **envp){
// 	printf("%s\n", get_fp("ls", envp));
// }
