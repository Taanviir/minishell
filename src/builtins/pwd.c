/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:39:33 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/20 13:53:55 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		write(2, "pwd: too many arguments\n", 25);
		return (1);
	}
	argv++;
	while (ft_strncmp("PWD=", *envp, 4))
		envp++;
	while (*(*envp + 4))
	{
		write(1, *envp + 4, 1);
		(*envp)++;
	}
	ft_putchar_fd('\n',1);
}
