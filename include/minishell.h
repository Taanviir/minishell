/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:43:03 by tanas             #+#    #+#             */
/*   Updated: 2023/08/07 11:55:10 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // write, access, close, fork, execve, dup, dup2, pipe, unlink
# include <readline/readline.h> // readline
# include <readline/history.h> // rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <sys/types.h> // wait, waitpid, wait3, wait4, kill
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/ioctl.h> // ioctl
# include <dirent.h> // opendir, readdir, closedir
# include <string.h> // strerror
# include <errno.h> // perror
# include <termios.h> // tcsetattr, tcgetattr
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <fcntl.h> // open
# include <stdbool.h> // bool
# include <stdint.h>
# include <sys/wait.h> // is wait not allowed?
# include "../libft/include/libft.h" // libft
# include "tokenizer.h"
# include "builtins.h"

typedef struct s_signal
{
	int	sigint;
	int	sigquit;
	int	exit_status;
}	t_signal;

// EXIT_STATUS
extern t_signal	g_signal;

// ERROR CODES
# define ERR_ARGS 1

// COLOR CODES
# define MAGENTA_B "\033[1;35m"
# define RED_B "\033[1;31m"
# define BLUE "\033[1;94m"
# define WHITE "\033[0m"

// SIGNAL FUNCTIONS
void	receive_signal(void);

// ENVIRONMENT FUNCTIONS
void	free_env_node(t_env **env);
void	free_env_list(t_env **env);
void	environment_init(t_env **env, char **envp);
void	add_node_bottom(t_env **head, char *envp);

// INPUT FUNCTION
t_cmd	*get_cmd(char **envp, char *line);

// EXECUTION FUNCTION
void	runcmd(t_cmd *cmd, char **envp, t_env **env);

// UTILS
int		length(char *str1, char *str2);

#endif
