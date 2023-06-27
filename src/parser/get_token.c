/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:29:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/06/27 02:17:38 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char *INPUT_TEST[100] = {
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
    "chmod +x script.sh",
    "ps aux",
    "kill PID",
    "find /path/to/directory -name \"*.txt\"",
    "tar -czvf archive.tar.gz directory/",
    "ssh username@hostname",
    "wget http://example.com/file.zip",
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
    "if [ -f file.txt ]; then echo 'File exists'; else echo 'File does not exist'; fi",
    "for i in 1 2 3; do echo $i; done",
    "while true; do echo 'Looping'; sleep 1; done",
    "case $VAR in option1) echo 'Option 1';; option2) echo 'Option 2';; *) echo 'Default option';; esac",
    "function say_hello() { echo 'Hello'; }; say_hello",
    "my_var='Hello'; echo $my_var",
    "my_array=(value1 value2 value3); echo ${my_array[1]}",
    "my_command() { echo 'Custom command'; }; my_command",
    "ls -l | grep pattern",
    "((num = 2 + 3)); echo $num",
    "if [[ $VAR == 'value' ]]; then echo 'Match'; fi",
    "echo $((RANDOM % 100))",
    "echo $((1 / 3))",
    "expr 5 + 2",
    "expr 10 - 3",
    "expr 5 \\* 2",
    "expr 10 / 3",
    "expr 15 % 4",
    "echo $[2+2]",
    "((num = 5)); ((num += 2)); echo $num",
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
    "ls -l | grep pattern | wc -l",
    "ls -l | grep pattern > output.txt",
    "ls -l | grep pattern >> output.txt",
    "command1 && command2 || command3",
    "command1 || command2 && command3",
    "command1 | command2 | command3",
    "''",                        // Empty single quotes
    "\"\"",
	"\"echo $(PATH)\"",
	NULL
	};
 */
/* define ALL for testing all test cases in input array */

bool	is_whitespace(char c)
{
	char const	*ws;
	int			i;

	ws = " \t\r\n\v";
	i = 0;
	while (ws[i])
	{
		if (!c || c == ws[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_operator(char c)
{
	char const	*opr;
	int			i;

	opr = "<|>&;(){}=$";
	i = 0;
	while (opr[i])
	{
		if (!c)
			return (false);
		else if (c == opr[i])
			return (true);
		i++;
	}
	return (false);
}

/* returns the type of a token, helper function for get_token */
static char	find_type(char **s)
{
	int	single_q;
	int	double_q;

	double_q = 0;
	single_q = 0;
	if (!**s)
		return (0);
	else if (is_operator(**s))
	{
		if (**s == '>' && *(*s + 1) && *(*s + 1) == '>')
		{
			*s += 1;
			return ('+');
		}
		else
			return (**s);
	}
	if (**s == '\'')
		single_q = 1;
	else if (**s == '\"')
		double_q = 1;
	while ((*(*s + 1) && (single_q || double_q)) || (!is_whitespace(*(*s + 1)) && !is_operator(*(*s + 1))))
	{
		*s += 1;
		if (**s == '\'')
			return ('a');
	}
	return ('a');
}

/*
* Returns the type of token as a char
	- '<' returns '<'
	- '>>' returns +
	- 'a' anything thats not an operator
* Advances the b_start to point to the next token in the buffer
* Sets the q and eq pointers to point to the begining and end
* 	of the token respectively
? note: buffer is the return of readline
*/
char	get_token(char **b_start, char *b_end,
				char **q, char **eq)
{
	char	ret;
	char	*s;

	s = *b_start;
	while (s < b_end && is_whitespace(*s))
		s++;
	if (q)
		*q = s;
	ret = find_type(&s);
	if (*s)
		s++;
	if (eq)
		*eq = s;
	while (s < b_end && is_whitespace(*s))
		s++;
	*b_start = s;
	return (ret);
}

/* #ifdef ALL

int main(void)
{
	char *b_start;
	char *b_end;
	char *q;
	char *eq;
	char ret;

	for (int i = 0; INPUT_TEST[i]; i++) {
		b_start = INPUT_TEST[i];
		b_end = b_start + strlen(b_start);
		printf("case : '%s'\n", b_start);
		while (*b_start) {
			q = b_start;
			eq = b_start;
			ret = get_token(&b_start, b_end, &q, &eq);
			printf("%-30.*s", (int)(eq - q), q);
			printf("\t\t\ttype : %c\n", ret);
		}
		printf("---------------------------------------------\n");
	}
}
#endif

#ifdef CASE
int main(int argc, char **argv)
{
	char *b_start;
	char *b_end;
	char *q;
	char *eq;
	char ret;

	b_start = "grep pattern < input.txt > output.txt";
	b_end = b_start + strlen(b_start);
	printf("case : '%s'\n", b_start);
	while (*b_start) {
		q = b_start;
		eq = b_start;
		ret = get_token(&b_start, b_end, &q, &eq);
		printf("%-30.*s", (int)(eq - q), q);
		printf("\ttype : %c\n", ret);
	}
	printf("-------------------------------------------------------\n");

}
#endif
 */

