/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:49:22 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/08 14:42:08 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieve the full path of a given program.
 *
 * This function attempts to get the full path of the program by concatenating it
 * with paths from the environment variable PATH. Before attempting this, it checks
 * if the given program_name can be directly executed, indicating an absolute path.
 * If the path is absolute, the absolute_path flag is set to true.
 *
 * @param program_name The name of the program to search for.
 * @param absolute_path A pointer to a flag that is set if the path is absolute.
 *
 * @return The full path to the program if found, otherwise NULL.
 */
static char	*get_fp(char *program_name, bool *absolute_path)
{
	char	*fp;
	char	**path;
	int		i;

	i = -1;
	// Check if the program can be executed directly (indicating an absolute path).
	if (program_name && !access(program_name, X_OK))
	{
		*absolute_path = true;
		return (program_name);
	}
	path = ft_split(getenv("PATH"), ':');
	// Iterate over each directory in the PATH, attempting to form the full path.
	while (path[++i])
	{
		fp = ft_bigjoin(3, path[i], "/", program_name);
		// If the constructed path points to an executable file, break from the loop.
		if (fp && !access(fp, X_OK))
			break ;
		free(fp);
		fp = NULL;
	}
	free_double_ptr((void **)path);
	return (fp);
}

void	execute_cmd(t_cmd *cmd, char **envp, t_env **env)
{
	t_exec	*execcmd;
	char	*fp;
	bool	absolute_path;

	absolute_path = false;
	execcmd = (t_exec *)cmd;
	if (!execcmd->argv[0]) // ! test with commenting this out
		return ;
	if (execute_builtin(cmd, envp, env)) // attempt to execute as a builtin
		return ;
	fp = get_fp(execcmd->argv[0], &absolute_path); // concatenate the path to command (argv[0])
	if (!fp)
	{
		printf("%s: command not found\n", fp);
		return ;
	}
	if (!fork()) {
		execve(fp, execcmd->argv, envp);
	if (!absolute_path)
		free(fp);
	write(2, "minishell: ", 11);
	write(2, fp, ft_strlen(fp));
	perror(": ");
	free_tree(cmd);
	exit(0);
	}
	wait(0);
	if (!absolute_path)
		free(fp);
}

static void write_filepath
