/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:43:03 by tanas             #+#    #+#             */
/*   Updated: 2023/07/19 10:30:06 by tanas            ###   ########.fr       */
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
#include <assert.h>
# include "../libft/include/libft.h" // libft
# include "tokenizer.h"
# include "tokenizer/type.h"
# include "builtins.h"

// EXIT_STATUS
// extern int exit_status;

// ERROR CODES
# define ERR_ARGS 1

// COLOR CODES
# define MAGENTA_B "\033[1;35m"
# define RED_B "\033[1;31m"
# define WHITE "\033[0m"

void	receive_signal(void);
char	get_token(char **incmd, char *tkend, char **q, char **eq);
t_cmd	*get_cmd(char **envp);

#endif
