/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:44:15 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/10 17:06:08 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper error function
static void	write_exec_error(char *program_name);

/**
 * Retrieve the full path of a given program.
 *
 * This function tries to find the full path of the program by checking each directory
 * in the PATH environment variable.
 *
 * @param program_name Name of the program to locate.
 *
 * @return Full path to the program if found; otherwise, NULL.
 */
static char	*get_full_path(char *program_name)
{
	char	*full_path;
	char	**path;
	int		i;

	i = -1;
	path = ft_split(getenv("PATH"), ':'); // TODO: Address potential issues with getenv
	// Iterate over directories in PATH, attempting to construct and verify the full path.
	while (path[++i])
	{
		full_path = ft_bigjoin(3, path[i], "/", program_name);
		// If the constructed path points to an executable file, break from the loop.
		if (full_path && !access(full_path, X_OK))
			break ;
		free(full_path);
		full_path = NULL;
	}
	free_double_ptr((void **)path);
	return (full_path);
}

/**
 * Execute a command, handling built-in commands and others.
 *
 * This function first checks if the command is a built-in; if it is, it executes the built-in.
 * If not a built-in, it attempts to execute the command either as an absolute path or by
 * locating it within the system's PATH environment variable. If the command fails to execute
 * in both scenarios, an error message is displayed.
 *
 * @param cmd      A structure holding command details.
 * @param envp     Custom environment structure
 * @param env      Environment variables as key-value pairs.
 */
void	execute_cmd(t_cmd *cmd, char **envp, t_env **env)
{
	t_exec	*execcmd;
	char	*program_name;
	char	*full_path;

	// Typecast the cmd structure to access command-specific parameters.
	execcmd = (t_exec *)cmd;
	program_name = execcmd->argv[0];
	// If the command is a builtin, execute it and return.
	if (execute_builtin(cmd, envp, env))
		return ;
	if (!fork()) // TODO: Add error handling for the fork call and program existence.
	{
		full_path = get_full_path(program_name);
		// Attempt to execute as absolute path or from PATH. If both fail, write an appropriate error.
		if ((execve(program_name, execcmd->argv, envp) && !full_path)
			|| (execve(full_path, execcmd->argv, envp))) {
				write_exec_error(program_name);
			}
		// Free command tree in the child process.
		free_tree(cmd);
		exit(0);
	}
	wait(0);
}

// helper function that takes program name and writes error it encountered
static void	write_exec_error(char *program_name)
{
	write(2, "minishell: ", 11);
	if (errno == EFAULT || errno == ENOENT)
	{
		write(2, program_name, ft_strlen(program_name));
		write(2, ": command not found\n", 21);
	}
	else
		perror(program_name);
}
