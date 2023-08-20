/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:48:42 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/19 21:44:13 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes both read and write ends of the pipe.
 *
 * @param p The array holding the file descriptors of the pipe ends.
 */
static void	close_pipe_ends(int *p);
/**
 * @brief Checks if a pipe was created successfully.
 *
 * In case of an error during pipe creation, prints the error.
 *
 * @param pipe_return The return value from the pipe() system call.
 * @return true if the pipe was created successfully, false otherwise.
 */
static bool	verify_pipe(int pipe_return);

// TODO child get correct exit status
/**
 * Executes a pipe node, connecting the standard outputs and inputs
 * of two commands.
 *
 * The function creates two child processes: one to handle the left command
 * (sending its output to the pipe), and another to handle the right command
 * (reading its input from the pipe).
 *
 * @param cmd		The pipe command structure.
 * @param env_list	Linked list of environment variables.
 */
void	execute_pipe(t_cmd *cmd, t_env **env_list)
{
	t_pipecmd	*pipecmd;
	int			pipe_fds[2];

	// Typecast the cmd structure to access pipe-specific parameters.
	pipecmd = (t_pipecmd *)cmd;
	// Create a pipe and check for success
	if (!verify_pipe(pipe(pipe_fds)))
		return ;
	// Fork for the left side of the pipe.
	if (!wfork())
	{
		dup2(pipe_fds[1], STDOUT_FILENO);
		close_pipe_ends(pipe_fds);
		runcmd(pipecmd->left, env_list);
		free_tree(cmd);
		free_list(*env_list);
		exit(WEXITSTATUS(g_exit_status));
	}
	// Fork for the right side of the pipe.
	else if (!wfork())
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		close_pipe_ends(pipe_fds);
		runcmd(pipecmd->right, env_list);
		free_tree(cmd);
		free_list(*env_list);
		exit(WEXITSTATUS(g_exit_status));
	}
	close_pipe_ends(pipe_fds);
	wait(&g_exit_status);
	wait(&g_exit_status);
}

// Closes both read and write ends of the pipe.
static void	close_pipe_ends(int *pipe_fds)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

// check pipe operation for errors
static bool	verify_pipe(int pipe_return)
{
	if (pipe_return < 0)
	{
		perror("");
		return (false);
	}
	return (true);
}
