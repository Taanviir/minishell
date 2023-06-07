#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>

#include "utils.h"

/* 
char *INPUT_TEST[] = {
		"ls -l",
		"cd /path/to/directory",
		"touch myfile.txt",
		"rm file.txt",
		"cp file.txt newfile.txt",
		"mv file.txt newdirectory/",
		"mkdir newdirectory",
		"rmdir emptydirectory",
		"echo \"Hello, World!\"",
		"cat myfile.txt",
		"grep \"pattern\" file.txt",
		"grep \"pattern\"    file.txt",
		"chmod +x script.sh",
		"./script.sh",
		"ps aux",
		"top",
		"kill PID",
		"find /path/to/directory -name \"*.txt\"",
		"tar -czvf archive.tar.gz directory/",
		"ssh username@hostname",
		"wget http://example.com/file.zip",
		"echo 'Single quotes'",
		"echo \"Double quotes\"",
		"echo \"Quotes within 'quotes'\"",
		"echo \"Quotes within \\\"quotes\\\"\"",
		"ls > files.txt",
		"cat < files.txt",
		"ls >> files.txt",
		"grep pattern < input.txt > output.txt",
		"echo 'Hello' >> file.txt 2>&1",
		"command | grep pattern",
		"command1 && command2",
		"command1 || command2",
		"command1; command2",
		"command1 &",
		"echo $HOME",
		"echo $PATH",
		"echo $USER",
		"echo $VAR",
		"echo ${VAR}",
		"echo $[2+2]",
		"if [ -f file.txt ]; then echo 'File exists'; else echo 'File does not exist'; fi",
		"for i in 1 2 3; do echo $i; done",
		"while true; do echo 'Looping'; sleep 1; done",
		"case $VAR in option1) echo 'Option 1';; option2) echo 'Option 2';; *) echo 'Default option';; esac",
		"function say_hello() { echo 'Hello'; }; say_hello",
		"my_var='Hello'; echo $my_var",
		"my_array=(value1 value2 value3); echo ${my_array[1]}",
		"my_array=(value1 value2 value3); echo ${my_array[@]}",
		"my_command() { echo 'Custom command'; }; my_command",
		"ls -l | grep pattern",
		"((num = 2 + 3)); echo $num",
		"echo $((5 * 4))",
		"if [[ $VAR == 'value' ]]; then echo 'Match'; fi",
		"[[ $VAR =~ ^[0-9]+$ ]] && echo 'Numeric'",
		"echo $((RANDOM % 100))",
		"echo $((1 / 3))",
		"expr 5 + 2",
		"expr 10 - 3",
		"expr 5 \\* 2",
		"expr 10 / 3",
		"expr 15 % 4",
		"echo $[2+2]",
		"((num = 5)); ((num += 2)); echo $num",
		"((num = RANDOM % 100)); echo $num",
		"awk '{ print $1 }' file.txt",
		"sed 's/pattern/replacement/' file.txt",
		"cut -d ':' -f 1 file.txt",
		"sort file.txt",
		"uniq file.txt",
		"head -n 5 file.txt",
		"tail -n 3 file.txt",
		"wc -l file.txt",
		"tee newfile.txt",
		"gzip file.txt",
		"gunzip file.txt.gz",
		"tar -xvf archive.tar",
		"awk 'BEGIN { print \"Start\" } { print $1 } END { print \"End\" }' file.txt",
		"sed -n '2,4p' file.txt",
		"cut -c 1-5 file.txt",
		"sort -r file.txt",
		"grep -i pattern file.txt",
		"head -n 10 file.txt | tail -n 5",
		"ls | grep pattern | wc -l",
		"command 2>&1 | tee output.txt",
		"find /path/to/directory -type f -name \"*.txt\"",
		"xargs -I {} mv {} newdirectory/",
		"sort file1.txt file2.txt > merged.txt",
		"paste file1.txt file2.txt > merged.txt",
		"comm file1.txt file2.txt",
		"diff file1.txt file2.txt",
		"man command",
		"info command",
		"apropos keyword",
		"history",
		"alias l='ls -l'",
		"unalias l",
		"source script.sh",
		"export VAR=value",
		"env",
		"echo $PWD",
		"uptime",
		"date",
		"cal",
		"whoami",
		"hostname",
		"clear",
		NULL
	};
 */
typedef struct	s_token
{
	char			*token; // mallocd needs to be freed aswell
	int				identifier; /* 0 operand, word 1 */
	struct s_token	*next;
}	t_token;
/* A simple command is an entry in the pipeline */
enum    token_type {OPR, WRD};
/*          (token)
             /   \
           OPR   WRD
Based on a list of operanads and words a simple command can be made
 */

t_token	*tkn_queue(char *input);

#define N_AVAILABLE_ARGS 32
typedef struct s_simple_command
{
	char	*name; // Wcommands name
	int		size_of_args;
	char	*args[N_AVAILABLE_ARGS]; // argument array
	int		rfiles[3]; /* 0 inFile, 1 outfile, 2 errfile array of file descriptors to redirect a stream to, (ex. direct stdin to pipe)*/
	int		background;
	struct s_simple_command *next;
}t_simple_command;

t_token	*parse(char *input); /* Parses the token queue into a queue of simple commands */

/* token functions */



#endif

// TODO queue needs to be made into an FIFO API since its reused
