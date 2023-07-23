/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:53:59 by tanas             #+#    #+#             */
/*   Updated: 2023/07/22 19:45:28 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_echo(int argc, char **argv)
// {
//   int	show_newline;
//   int	length;

// 	show_newline = 1;
// 	argv++;
// 	argc--;
// 	while (!ft_strncmp("-n", *argv, ft_strlen(*argv)))
// 	{
// 		show_newline = 0;
// 		argv++;
// 		argc--;
// 	}
// 	while (argc)
// 	{
// 		argc--;
// 		length = ft_strlen(*argv);
// 		write(1, *argv, length);
// 		if (argc)
// 			ft_putchar_fd(' ', 1);
// 		else if (show_newline)
// 			ft_putchar_fd('\n',1);
// 		argv++;
// 	}
// 	return (0);
// }
