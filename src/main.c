/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:46:53 by tanas             #+#    #+#             */
/*   Updated: 2023/08/02 22:00:26 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test/test.h"
#include "minishell.h"
#include <unistd.h>

t_signal g_signal;

#ifdef TEST
t_cmd *get_cmd(char **envp, char *line) {
  t_cmd *root;
  char *dir;
  char *prompt;

  dir = getcwd(NULL, 0);
  prompt = ft_bigjoin(6, MAGENTA_B, "ghost@shell:", BLUE, dir, " → ", WHITE);
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
t_cmd *get_cmd(char **envp, char *line) {
  char *dir;
  char *prompt;
  t_cmd *root;

  dir = getcwd(NULL, 0);
  prompt = ft_bigjoin(6, MAGENTA_B, "ghost@shell:", BLUE, dir, " → ", WHITE);
  dup2(STDERR_FILENO, STDOUT_FILENO);
  line = readline(prompt);
  free(prompt);
  free(dir);
  if (!line)
    return (ft_exit(), NULL);
  add_history(line);
  root = parsecmd(line, envp);
  return (root);
}
#endif

int main(int argc, char **argv __attribute__((unused)), char **envp) {
  char *line;

  if (argc != 1)
    return (printf(RED_B "Error: %s\n" WHITE, strerror(E2BIG)), ERR_ARGS);
  receive_signal();
  while (g_signal.exit_status == 0) {
    line = NULL;
    runcmd(get_cmd(envp, line), envp);
    free(line);
  }
  // rl_clear_history();
  return (EXIT_SUCCESS);
}
