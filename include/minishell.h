/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:43:03 by tanas             #+#    #+#             */
/*   Updated: 2023/06/26 16:20:21 by sabdelra         ###   ########.fr       */
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
# include <assert.h>
# include "../libft/include/libft.h" // libft
# include "tokenizer.h"
# include "tokenizer/type.h"

// ERROR CODES
# define ERR_ARGS 1

// COLOR CODES
# define MAGENTA_B "\033[1;35m"
# define RED_B "\033[1;31m"
# define WHITE "\033[0m"

// TYPEDEFS
void	receive_signal(void);
char	get_token(char **incmd, char *tkend, char **q, char **eq);

// queue api, might not be needed
t_queue	*create_queue(void);
void	enqueue(void *new, t_queue *q);

#endif
