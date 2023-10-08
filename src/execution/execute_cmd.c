/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:20:43 by tanas             #+#    #+#             */
/*   Updated: 2023/10/07 20:48:53 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper error function
static void	write_exec_error(char *program_name, int *l_exit);

// helper function that checks if a string has consecutive slashes
bool	has_consecutive_slashes(char *str)
{
	while (*str)
	{
		if (*str == '/' && *(str + 1) == '/')
			return (true);
		str++;
	}
	return (false);
}

/**
 * Retrieve the full path of a given program.
 *
 * This function tries to find the full path of the program by checking
 * each directory in the PATH environment variable.
 *
 * @param program_name Name of the program to locate.
 * @param env_list Environment list.
 *
 * @return Full path to the program if found; otherwise, NULL.
 */
static char	*get_full_path(char *program_name, t_env **env_list)
{
	char	*full_path;
	char	**path;
	int		i;

	i = -1;
	full_path = NULL;
	if (has_consecutive_slashes(program_name))
		return (full_path);
	path = ft_split(get_env(*env_list, "PATH")->value, ':');
	if (!path || !*program_name)
		return (free_double_ptr((void **)path), NULL);
	while (path[++i])
	{
		full_path = ft_bigjoin(3, path[i], "/", program_name);
		if (full_path && !access(full_path, X_OK))
			break ;
		free(full_path);
		full_path = NULL;
	}
	free_double_ptr((void **)path);
	if (!full_path)
		return (ft_strdup(program_name));
	return (full_path);
}

static int	execute_builtin(t_cmd *cmd, t_env **env_list)
{
	t_exec	*exec;
	char	**argv;

	exec = (t_exec *) cmd;
	argv = exec->argv;
	if (!argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "echo", get_len(argv[0], "echo")))
		return (ft_echo(exec->argc, exec->argv, *env_list));
	if (!ft_strncmp(argv[0], "cd", get_len(argv[0], "cd")))
		return (ft_cd(argv, env_list));
	else if (!ft_strncmp(argv[0], "pwd", get_len(argv[0], "pwd")))
		return (ft_pwd());
	else if (!ft_strncmp(argv[0], "export", get_len(argv[0], "export")))
		return (ft_export(argv, env_list));
	else if (!ft_strncmp(argv[0], "unset", get_len(argv[0], "unset")))
		return (ft_unset(argv, env_list));
	else if (!ft_strncmp(argv[0], "env", get_len(argv[0], "env")))
		return (ft_env(argv, env_list));
	else if (!ft_strncmp(argv[0], "exit", get_len(argv[0], "exit")))
		return (ft_exit(cmd, env_list));
	return (EXECUTE_CHILD);
}

/**
 * Execute a command, handling built-in commands and others.
 *
 * This function first checks if the command is a built-in; if it is,
 * it executes the built-in. If not a built-in, it attempts to execute the
 * command either as an absolute path or by locating it within the system's
 * PATH environment variable. If the command fails to execute in both
 * scenarios, an error message is displayed.
 *
 * @param cmd      A structure holding command details.
 * @param env_list Environment list.
 * @param root     Root variable.
 */
void	execute_cmd(t_cmd *cmd, t_env **env_list, t_cmd *root)
{
	t_exec	*execcmd;
	char	*program_name;
	char	*full_path;
	char	**env_array;

	execcmd = (t_exec *)cmd;
	program_name = execcmd->argv[0];
	g_exit_status = (execute_builtin(cmd, env_list) << 8);
	if ((g_exit_status >> 8) != EXECUTE_CHILD)
		return ;
	if (!wfork())
	{
		env_array = list_to_array(*env_list);
		full_path = get_full_path(program_name, env_list);
		if (ft_strchr(full_path, '/')
			&& execve(full_path, execcmd->argv, env_array))
			write_exec_error(program_name, &g_exit_status);
		else
			write_exec_error(program_name, &g_exit_status);
		cleanup_exec(full_path, root, env_array, *env_list);
		exit(g_exit_status);
	}
	wait(&g_exit_status);
}

// helper function that takes program name and writes error it
// encountered and sets the appropriate exit status
static void	write_exec_error(char *program_name, int *l_exit)
{
	struct stat	file_stat;

	ft_putstr_fd("minishell: ", 2);
	if (stat(program_name, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd(program_name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		*l_exit = 126;
	}
	else if (errno == EACCES || errno == ENOENT)
	{
		ft_putstr_fd(program_name, 2);
		if (errno == ENOENT)
		{
			ft_putstr_fd(": command not found\n", 2);
			*l_exit = 127;
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd(": Permission denied\n", 2);
			*l_exit = 126;
		}
	}
	else
		perror(program_name);
}
