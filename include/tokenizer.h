/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:59:44 by sabdelra          #+#    #+#             */
/*   Updated: 2023/06/26 16:48:07 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Bash Grammar could be written in a format called "Backus-Naur Form"

cmd [arg]* [|cmd [arg]* ]* [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]
- an example of shell grammar in Backus-Naur form
*/

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <stdint.h> // variable types

/* A node in the queue can be any type of struct */
typedef struct s_node
{
	void			*data; /* can be any type of struct */
	struct s_node	*next;
}	t_node;

/* QUEUE FIFO implementation */
typedef struct s_queue
{
	t_node	*first;
	t_node	*last;
	size_t	size;
}	t_queue;

/* A token is a character or a group of characters recognized from the input stream. */
typedef struct s_token
{
	char			*token; // mallocd needs to be freed aswell
	u_int32_t		identifier; /* 0 operand, word 1 */
}	t_token;

# define N_AVAILABLE_ARGS 32

/* A simple command is an entry in the pipeline */
typedef struct s_simple_command
{
	char	*name; // commands name
	int		size_of_args;
	char	*args[N_AVAILABLE_ARGS]; // argument array
	int		rfiles[3]; /* 0 inFile, 1 outfile, 2 errfile array of file descriptors to redirect a stream to, (ex. direct stdin to pipe)*/
	int		background;
	struct s_simple_command	*next;
}	t_simple_command;

extern char *INPUT_TEST[100];


/* input commands test cases keep adding here */
// char *INPUT_TEST[108] = {
// 	"ls -l",
// 	"cd /path/to/directory",
// 	"touch myfile.txt",
// 	"rm file.txt",
// 	"cp file.txt newfile.txt",
// 	"mv file.txt newdirectory/",
// 	"mkdir newdirectory",
// 	"rmdir emptydirectory",
// 	"echo \"Hello, World!\"",
// 	"cat myfile.txt",
// 	"grep \"pattern\" file.txt",
// 	"grep \"pattern\"    file.txt",
// 	"chmod +x script.sh",
// 	"./script.sh",
// 	"ps aux",
// 	"top",
// 	"kill PID",
// 	"find /path/to/directory -name \"*.txt\"",
// 	"tar -czvf archive.tar.gz directory/",
// 	"ssh username@hostname",
// 	"wget http://example.com/file.zip",
// 	"echo 'Single quotes'",
// 	"echo \"Double quotes\"",
// 	"echo \"Quotes within 'quotes'\"",
// 	"echo \"Quotes within \\\"quotes\\\"\"",
// 	"ls > files.txt",
// 	"cat < files.txt",
// 	"ls >> files.txt",
// 	"grep pattern < input.txt > output.txt",
// 	"echo 'Hello' >> file.txt 2>&1",
// 	"command | grep pattern",
// 	"command1 && command2",
// 	"command1 || command2",
// 	"command1; command2",
// 	"command1 &",
// 	"echo $HOME",
// 	"echo $PATH",
// 	"echo $USER",
// 	"echo $VAR",
// 	"echo ${VAR}",
// 	"echo $[2+2]",
// 	"if [ -f file.txt ]; then echo 'File exists'; else echo 'File does not exist'; fi",
// 	"for i in 1 2 3; do echo $i; done",
// 	"while true; do echo 'Looping'; sleep 1; done",
// 	"case $VAR in option1) echo 'Option 1';; option2) echo 'Option 2';; *) echo 'Default option';; esac",
// 	"function say_hello() { echo 'Hello'; }; say_hello",
// 	"my_var='Hello'; echo $my_var",
// 	"my_array=(value1 value2 value3); echo ${my_array[1]}",
// 	"my_array=(value1 value2 value3); echo ${my_array[@]}",
// 	"my_command() { echo 'Custom command'; }; my_command",
// 	"ls -l | grep pattern",
// 	"((num = 2 + 3)); echo $num",
// 	"echo $((5 * 4))",
// 	"if [[ $VAR == 'value' ]]; then echo 'Match'; fi",
// 	"[[ $VAR =~ ^[0-9]+$ ]] && echo 'Numeric'",
// 	"echo $((RANDOM % 100))",
// 	"echo $((1 / 3))",
// 	"expr 5 + 2",
// 	"expr 10 - 3",
// 	"expr 5 \\* 2",
// 	"expr 10 / 3",
// 	"expr 15 % 4",
// 	"echo $[2+2]",
// 	"((num = 5)); ((num += 2)); echo $num",
// 	"((num = RANDOM % 100)); echo $num",
// 	"awk '{ print $1 }' file.txt",
// 	"sed 's/pattern/replacement/' file.txt",
// 	"cut -d ':' -f 1 file.txt",
// 	"sort file.txt",
// 	"uniq file.txt",
// 	"head -n 5 file.txt",
// 	"tail -n 3 file.txt",
// 	"wc -l file.txt",
// 	"tee newfile.txt",
// 	"gzip file.txt",
// 	"gunzip file.txt.gz",
// 	"tar -xvf archive.tar",
// 	"awk 'BEGIN { print \"Start\" } { print $1 } END { print \"End\" }' file.txt",
// 	"sed -n '2,4p' file.txt",
// 	"cut -c 1-5 file.txt",
// 	"sort -r file.txt",
// 	"grep -i pattern file.txt",
// 	"head -n 10 file.txt | tail -n 5",
// 	"ls | grep pattern | wc -l",
// 	"command 2>&1 | tee output.txt",
// 	"find /path/to/directory -type f -name \"*.txt\"",
// 	"xargs -I {} mv {} newdirectory/",
// 	"sort file1.txt file2.txt > merged.txt",
// 	"paste file1.txt file2.txt > merged.txt",
// 	"comm file1.txt file2.txt",
// 	"diff file1.txt file2.txt",
// 	"man command",
// 	"info command",
// 	"apropos keyword",
// 	"history",
// 	"alias l='ls -l'",
// 	"unalias l",
// 	"source script.sh",
// 	"export VAR=value",
// 	"env",
// 	"echo $PWD",
// 	"uptime",
// 	"date",
// 	"cal",
// 	"whoami",
// 	"hostname",
// 	"clear",
// 	NULL
// };
                      // Empty double quotes
#endif
