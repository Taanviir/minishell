/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:45:17 by tanas             #+#    #+#             */
/*   Updated: 2023/06/18 17:45:34 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// test each stage seperatly
// 2 - parsing
//			. chatgpt 1000 random bash commands for testing
//			. wrong input ...
//			. keep adding items to those lists

#include "minishell.h"

// COLORS
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_END "\033[0m"

#define AUTHOR "samih/tanvir"

#define PROGRAM_NAME "minishell"

/* Main loop -- the main loop of the program */
// static void	main_loop(void)
// {
// 	char				*input_command; // a line inserted by the user
// 	int					status;
// 	t_simple_command	*sc;

// 	do {
// 		fprintf(stdout, "\033[0;32m%s@\033[0;35m%s\033[0m~>>", PROGRAM_NAME, USER);
// 		fflush(stdout);
// 		/* The shell shall read its input in terms of lines from a file */
// 		input_command = get_next_line(STDIN_FILENO);
// 		/* input is parsed using two major modes, ordinary token recognition and processing of here-documents */
// 		sc = parse(input_command); /* the input is parsed into a data collection 'command_table' A 2 queues -words and -operators */
// 		// execute(sc);
// 		(void)(sc);
// 		status = 1;
// 	}	while (status);
// }

// int
// main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **envp)
// {
// 	(void)envp;
// 	main_loop();
// }
