/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/08/09 21:12:40 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test/test.h"
#include "minishell.h"

t_signal g_signal;

static char	*get_dir(void)
{
	char	*dir;
	char	*last;
	char	*temp;


	dir = getcwd(NULL, 0);
	if (!ft_strncmp(dir, getenv("HOME"), ft_strlen(dir)))
	{
		free(dir);
		dir = ft_strdup("[~]");
	}
	else
	{
		last = ft_strrchr(dir, '/');
		if (last)
		{
			temp = ft_bigjoin(3, "[", last + 1, "]");
			free(dir);
			dir = temp;
		}
	}
	return (dir);
}

#ifdef TEST
t_cmd *get_cmd(char **envp, char *line)
{
	t_cmd *root;
	char *dir;
	char *prompt;

	dir = get_dir();
	prompt = ft_bigjoin(3, MAGENTA_B "ghost@shell:" BLUE, dir, " → " WHITE);
	line = readline(MAGENTA_B "ghost@shell → " WHITE);
	free(prompt);
	free(dir);
	if (!line)
		return (ft_exit(0), NULL);
	add_history(line);
	root = parsecmd(line, envp);
	test(root);
	return (root);
}
#else
t_cmd *get_cmd(char *line, char **envp, t_env **env)
{
	char	*dir;
	char	*prompt;
	t_cmd	*root;

	dir = get_dir();
	prompt = ft_bigjoin(3, MAGENTA_B "ghost@shell:" BLUE, dir, " → " WHITE);
	//! way too many problems caused by this shit
	// write(2, prompt, ft_strlen(prompt)); //! writing prompt to stderr
	// rl_already_prompted = 1;
	line = readline(prompt);
	free(prompt);
	free(dir);
	if (!line)
		return (ft_exit(0, env), NULL);
	add_history(line);
	root = parsecmd(line, envp);
	return (root);

}
#endif

int main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char	*line;
	t_env	*env;

	if (argc != 1)
		return (printf(RED_B "Error: %s\n" WHITE, strerror(E2BIG)), ERR_ARGS);
	receive_signal();
	environment_init(&env, envp);
	//TODO unset env that need to be unset
	//TODO increase $SHLVL by 1
	// line = ft_strdup("unset OLDPWD ");
	// runcmd(parsecmd(line, envp), envp, &env);
	// free(line);
	while (g_signal.exit_status == 0)
	{
		line = NULL;
		// default
		free_tree(runcmd(get_cmd(line, envp, &env), envp, &env));
		receive_signal();
		free(line);
	}
	free_env_list(&env);
	// rl_clear_history();
	return (EXIT_SUCCESS);
}
