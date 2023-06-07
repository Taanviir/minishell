// test each stage seperatly
// 1 - the data structure queue and token
//			. check memory leaks
//			. empty queues 1 item, 2, 1000 ... etc
//			. put only 1 item in the que and dque it
//			. dque regular, dque last item in the que, dque an empty que
// 2 - parsing
//			. chatgpt 1000 random bash commands for testing
//			. wrong input ...
//			. keep adding items to those lists

#include "../include/ft_error.h"
#include "../include/interpreter.h"
#include "../include/utils.h"
#include "../include/interpreter/type.h"
#include "../include/gnl.h"
#include <assert.h>


// COLORS
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_END "\033[0m"

#define USER "eva001"

#define PROGRAM_NAME "minishell"

/* Main loop -- the main loop of the program */
void	main_loop(void)
{
	char				*input; // a line inserted by the user
	int					status;
	// t_simple_command	*sc;
	t_token	*sc;

	do {
		fprintf(stdout, "\033[0;32m%s@\033[0;35m%s\033[0m~>>", PROGRAM_NAME, USER);
		fflush(stdout);
		/* The shell shall read its input in terms of lines from a file */
		input = get_next_line(STDIN_FILENO);
		/* input is parsed using two major modes, ordinary token recognition and processing of here-documents */
		sc = parse(input); /* the input is parsed into a data collection 'command_table' A 2 queues -words and -operators */
		printf("(%s)\n", input);
		printf("%s", sc->token);
		printf(", type: %s\n", sc->identifier == OPR? "OPR":"WORD");
		printf("______________________________\n");
		status = 1;
	}	while (status);
}

int
main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **envp)
{
    (void)envp;
    main_loop();
}
