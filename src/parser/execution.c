/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:00:29 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/26 00:04:49y sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_fp(char *program_name, char **envp)
{
	char	*fp;
	char	**path;
	int		i;

	i = 0;
	fp = NULL;
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	path = ft_split(*envp + 5, ':');
	while (path[i])
	{
		fp = ft_strjoin(ft_strjoin(ft_strdup(path[i]), "/"), program_name);
		if (!access(fp, X_OK))
		{
			while (path[i])
				free(path[i++]);
			free(path);
			return (fp);
		}
		free(path[i]);
		free(fp);
		i++;
	}
	free(path);
	return (NULL);
}

static void	execute_cmd(t_cmd	*cmd, char **envp)
{
	t_exec		*execcmd;

	execcmd = (t_exec *)cmd;
	if (!execcmd->argv[0]) // no command
		exit(EXIT_FAILURE);
	execve(get_fp(execcmd->argv[0], envp), execcmd->argv, envp); // what happens when you pass execve a NULL
	write(2, "program not found\n", 18);
}

static void execute_redir(t_cmd *cmd, char **envp)
{
	t_redircmd	*redircmd;
	int			new_fd;

	redircmd = (t_redircmd *)cmd;
	new_fd = open(redircmd->fp, redircmd->mode);
	if (new_fd < 0) // open error
		write(2, "failed to open\n", 16);
	dup2(new_fd, redircmd->fd);
	runcmd(redircmd->cmd, envp);
}

static void execute_pipe(t_cmd *cmd, char **envp)
{
	t_pipecmd	*pipecmd;
	int			p[2];

	pipecmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
		write(2, "failed to pipe\n", 16);
	if (!fork())
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		runcmd(pipecmd->left, envp);
	}
	if (!fork())
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		runcmd(pipecmd->right, envp);
	}
	close(p[0]);
	close(p[1]);
	wait(NULL);
	wait(NULL);
}

static void execute_bgcmd(t_cmd *cmd, char **envp)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	if (!fork())
		runcmd(bgcmd->cmd, envp);
}

static void execute_seq(t_cmd *cmd, char **envp)
{
	t_seqcmd	*seqcmd;

	seqcmd = (t_seqcmd *)cmd;
	if (!fork())
		runcmd(seqcmd->left, envp);
	wait(NULL);
	runcmd(seqcmd->right, envp);
}

typedef void(*execute)(t_cmd *cmd, char **envp);
execute executers[5] = {
	execute_cmd,
	execute_redir,
	execute_pipe,
	execute_seq,
	execute_bgcmd
};

void	runcmd(t_cmd *cmd, char **envp)
{
	if (!cmd)
		exit(EXIT_FAILURE);
	executers[cmd->type](cmd, envp);
}

// int main(int argc, char **argv, char **envp){
// 	printf("%s\n", get_fp("ls", envp));
// }
