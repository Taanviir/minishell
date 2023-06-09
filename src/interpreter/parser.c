#include "../../include/interpreter.h"
/* The interpreter passes on a queue (FIFO) linked list to the parser
of type t_token *token; a token can be either a WORD or OPERATOR
 The aim of this function here is to create the data structure struct s_simple_command; and ?? Compund_commands*/

#define TEST_ALL

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


/* returns true if the token is an operand, and false if else wise */
static bool	is_operand(char *token)
{
	int		i;
	char	*array_of_operands[] = {
	";",      // Command separator
	"&&",     // Logical AND
	"||",     // Logical OR
	"&",      // Run command in background
	"|",      // Pipe output to another command
	"<",      // Input redirection from file
	">",      // Output redirection to file (overwrite)
	">>",     // Output redirection to file (append)
	"<<",     // Here document
	"(",      // Start subshell
	")",      // End subshell
	"*",      // Wildcard (matches zero or more characters)
	"?",      // Wildcard (matches a single character)
	"[",      // Test command or file wildcard matching
	"]",      // Test command or file wildcard matching
	"$",      // Variable substitution
	"`",      // Command substitution
	"\"",     // Double quotes (preserve literal meaning of most characters)
	"'",      // Single quotes (preserve literal meaning of all characters)
	"\\n",    // Newline character
	"\\t",    // Tab character
	"\\r",    // Carriage return character
	"\\\"",   // Literal double quote character
	"\\'",    // Literal single quote character
	"\\$",    // Literal dollar sign character
	"\\\\",   // Literal backslash character
	NULL
};

	i = 0;
	while (array_of_operands[i])
	{
		if (!ft_strncmp(array_of_operands[i], token, ft_strlen(array_of_operands[i])))
			return (true);
		i++;
	}
	return (false);
}

/* takes a token queue as argument and sets the identifier of all the tokens in the que
to either word or operand */
static void set_type(t_queue *queue)
{
	t_token	*current;
	t_node	*temp;

	temp = queue->first;
	if (temp)
	{
		while (temp)
		{
			current = temp->data;
			if(is_operand(current->token))
				current->identifier = OPR;
			else
				current->identifier = WRD;
			temp = temp->next;
		}
	}
}

/* Parses the token queue into a simple command struct */
t_queue	*parse(char *input)
{
	t_queue				*token_queue;
	// t_simple_command	*sc;

	// sc = malloc(sizeof(t_queue));
	// if (!sc)
	// 	return (NULL);
	token_queue = tokenizer(input);
	set_type(token_queue);
	/*
	- set command name
	- set size_of_args
	- store in argument array
	- set redirections based on operators in the token_queue
	- set background flag
	- has a pointer to next command
	 */
	return token_queue;
}

#ifdef TEST_ALL
int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	int i = 0;
	for (char *test_case = INPUT_TEST[i]; test_case; i++, test_case = INPUT_TEST[i])
	{
		t_queue	*token_queue = parse(test_case);
		t_token	*current_token;

		printf("Test case no: %d\n", i + 1);
		printf("(%s)\n", test_case);
		for (t_node *temp = token_queue->first; temp; temp = temp->next)
		{
			current_token = temp->data;
			printf("%s ", current_token->token);
			printf(" type: %s\n", current_token->identifier == OPR? "OPR":"WORD");
		}
		printf("______________________________\n");
	}
}
#endif
