/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:43:03 by tanas             #+#    #+#             */
/*   Updated: 2023/08/24 20:47:37 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/wait.h>
# include <limits.h>
# include "../libft/include/libft.h"
# include "tokenizer.h"
# include "builtins.h"

// EXIT_STATUS
extern int	g_exit_status;

# define EXECUTE_CHILD 1000
# define QUIT_HEREDOC 5000

# define DELI_ERROR "syntax error near unexpected token `newline'"

// COLOR CODES
# define MAGENTA_B "\033[1;35m"
# define RED_B "\033[1;31m"
# define BLUE "\033[1;94m"
# define WHITE "\033[0m"

// SIGNAL FUNCTIONS
void	receive_signal(void);
void	signal_handler_parent(int signum);
void	signal_handler_child(int sig);
void	signal_handler_heredoc(int sig);

// ENVIRONMENT FUNCTIONS
void	environment_init(t_env **env, char **envp);
void	add_node_bottom(t_env **head, char *envp);
char	**list_to_array(t_env *env);
void	free_list(t_env *env);
char	*get_env(t_env *env_list, char *name);

// INPUT FUNCTION
t_cmd	*get_cmd(char *line, t_env **env_list);

// EXECUTION FUNCTION
t_cmd	*runcmd(t_cmd *cmd, t_env **env_list, t_cmd *root);

// UTIL FUNCTIONS
int		get_len(char *str1, char *str2);
char	*remove_quotes(char *q, char *eq);
bool	is_empty(char *line);
int		print_error(char *err_msg, char *function);
void	close_fds(t_cmd *root);

// WRAPPER FUNCTIONS
bool	verify_pipe(int pipe_return);
int		wfork(void);

// FREE FUNCTIONS
void	free_cmd(t_cmd *cmd);
void	free_tree(t_cmd *cmd);
void	free_two(char *str1, char *str2);

#endif
