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
#include "../include/token.h"
#include "../include/utils.h"
#include "../include/token/type.h"
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

t_ctable    *parse(char *input)
{
    t_ctable    *command_table;
    char        **tokens;

    tokens = ft_split(input, ' ');
    command_table = malloc(sizeof(t_ctable));
    if (!command_table) exit_clean();
    


}

/* Main loop -- the main loop of the program */
void    main_loop(void)
{
    char        *input; // a line inserted by the user
    char        **arguments; // the line split up into a 2-D array
    int         status;
    t_ctable    *command_table;

    do {
        fprintf(stdout, "\033[0;32m%s@\033[0;35m%s\033[0m~>>", PROGRAM_NAME, USER);
        fflush(stdout);
        input = get_next_line(STDIN_FILENO);
        command_table = parse(input); /* the input is parsed into a data collection 'command_table' A 2 queues -words and -operators */

        status = 1;
    } while (status);
}

int 
main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **envp)
{
    (void)envp;
    main_loop();
}