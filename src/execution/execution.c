/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/08/12 02:11:03 by sabdelra         ###   ########.fr       */
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
int	execute_builtin(t_cmd *cmd, char **envp, t_env **env)
{
	char *program;
	t_exec *execcmd;

	execcmd = (t_exec *)cmd;
	program = execcmd->argv[0];
	if (!program) //! check in case no program name
		return (0);
	if (!ft_strncmp(program, "echo", get_len(program, "echo")))
		return (ft_echo(execcmd->argv), 1);
	if (!ft_strncmp(program, "cd", get_len(program, "cd")))
		return (ft_cd(execcmd->argv, env), 1);
	else if (!ft_strncmp(program, "pwd", get_len(program, "pwd")))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(program, "export", get_len(program, "export")))
		return (ft_export(execcmd->argv, envp, env), 1);
	else if (!ft_strncmp(program, "unset", get_len(program, "unset")))
		return (ft_unset(execcmd->argv, env), 1);
	else if (!ft_strncmp(program, "env", get_len(program, "env")))
		return (ft_env(execcmd->argv, env), 1);
	else if (!ft_strncmp(program, "exit", get_len(program, "exit"))) {
		// TODO shit's weird homie, can't exit mid program
		free_tree(cmd);
    return (ft_exit(EXIT_SUCCESS, env), 1);
  }
	return (0);
}

/* TODO some missing behaviour how to call back to fg and update number */
static void	write_bg(void)
{
	char *pid;

	pid = ft_itoa((int)getpid());
	write(1, "[1] ", 4); // TODO update the number of bg processes
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
}
static void	execute_bgcmd(t_cmd *cmd, char **envp, t_env **env)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	if (!fork())
	{
		write_bg();
		runcmd(bgcmd->cmd, envp, env);
		free_tree(cmd);
		exit(0);
	}
	// wait(0);
}
/* TODO some missing behaviour how to call back to fg and update number */

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
