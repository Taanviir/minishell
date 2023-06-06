#include "../../include/interpreter.h"
// #include "../../include/utils.h"
#include "../../include/interpreter/type.h"
#include <string.h>
/*
Bash Grammar is written in a format called "Backus-Naur Form"
cmd [arg]* [|cmd [arg]* ]* [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]
This is an example of shell grammar in Backus-Naur form
*/


/* define TEST_ALL if you want to test all*/

/* Create a t_token, an entry into token linked list */
static t_token *create_token(char *token)
{
	t_token *new = malloc(sizeof(t_token));
	new->token = token;
	new->next = NULL;
	return (new);
}

/* Creates a string from the input, by finding the next token in the input */
static char	*next_token_string(char *input, size_t *i)
{
		char	*token;
		char	del;
		size_t	token_length;

		del = '\0';

		size_t start = *i;
		while (input[*i] && input[*i] != del)
		{
			if (!del && (input[*i] == '"' || input[*i] == '\''))
			{
				del = input[*i];
				start += 1; // to skip the delimiter
			}
			else if (!del || input[*i] == del)
				del = ' ';
			(*i)++;
		}
		token_length = *i - start;
		token = malloc(sizeof(char) * (token_length + 1));
		if (token)
		{
			strncpy(token, input + start, token_length);
			token[token_length] = '\0';
			return (token);
		}
		else
			return (NULL);
}

/* based on matching a pattern set the type field in t_simple_command
pattern is simple either an operator from a list, or no its a word */
/* splits up an input line into tokens with type enum{OPR,WRD} */
/* //!type not implemented yet */

enum TKN_QUEUE {
	first,
	prev,
	temp
};

t_token *tkn_queue(const char *input)
{

	t_token	*q[3]; /* position in que (first, prev, temp) */
	size_t	i;

	i = 0;
	while (input[i])
	{
		q[temp] = create_token(next_token_string(input, &i));
		/* adding q[new] token to queue FIFO */
		if (q[prev]) // this is the 2nd new onwards
			q[prev]->next = q[temp];
		if (!q[first])
		{
			q[first] = q[temp]; // new must be first one hmmmm!
			q[prev]= q[first];
		}
		else
			q[prev]= q[temp];
		if (input[i])
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
		}
	}
	q[temp]->next = NULL; // terminating the queuekz
	return (first); /* head of queue */
}

#ifdef TEST_ALL
int main(int argc, char **argv)
{
	char *input[] = {
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
	int i = 0;
	for (char *test_case = input[i]; test_case; i++, test_case = input[i])
	{
		t_token *token_queue_ll = tkn_queue(test_case);
		printf("Test case no: %d\n", i + 1);
		printf("(%s)\n", test_case);
		for (t_token *temp = token_queue_ll; temp; temp = temp->next)
			printf("%s\n", temp->token);
		printf("______________________________\n");
	}
}
#endif

#ifdef CASE_11
int main(int argc, char **argv)
{
	char *test = "grep \"pattern\" file.txt";
	t_token *head = tkn_queue(test);
}
#endif


// TODO case 30 "echo 'Hello' >> file.txt 2>&1" last token??
// TODO maybe quotes are supposed to be part of the token or no? depends on how it will be passed on to execve

