/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/08/07 21:22:34 by sabdelra         ###   ########.fr       */
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
  if (!ft_strncmp(dir, getenv("HOME"), ft_strlen(dir))) {
    free(dir);
    dir = ft_strdup("[~]");
  } else {
    last = ft_strrchr(dir, '/');
    if (last) {
      temp = ft_bigjoin(3, "[", last + 1, "]");
      free(dir);
      dir = temp;
    }
  }
  return (dir);
}

#ifdef TEST
t_cmd *get_cmd(char **envp, char *line) {
  t_cmd *root;
  char *dir;
  char *prompt;

  dir = get_dir();
  prompt = ft_bigjoin(3, MAGENTA_B "ghost@shell:" BLUE, dir, " → " WHITE);
  line = readline(MAGENTA_B "ghost@shell → " WHITE);
  free(prompt);
  free(dir);
  if (!line)
    return (ft_exit(), NULL);
  add_history(line);
  root = parsecmd(line, envp);
  test(root);
  return (root);
}
#else
t_cmd *get_cmd(char **envp, char *line)
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
    return (ft_exit(0), NULL);
  add_history(line);
  root = parsecmd(line, envp);
  return (root);

}
#endif

int main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char	*line;
	t_env	*env;
	t_cmd	*root;


	if (argc != 1)
		return (printf(RED_B "Error: %s\n" WHITE, strerror(E2BIG)), ERR_ARGS);
	receive_signal();
	// unset env that need to be unset
	environment_init(&env, envp);
	while (g_signal.exit_status == 0)
	{
		line = NULL;

		root = get_cmd(envp, line);
		runcmd(root, envp, &env);
		free(line);
	}
	free_env_list(&env);
	free_tree(root);
	// rl_clear_history();
	return (EXIT_SUCCESS);
}
