/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:21:33 by tanas             #+#    #+#             */
/*   Updated: 2023/07/08 14:52:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

// GET_NEXT_LINE FUNCTIONS
char	*get_next_line(int fd);
char	*get_line(char *str);
char	*read_file(int fd, char *stash);
char	*update_stash(char *old_stash);

#endif