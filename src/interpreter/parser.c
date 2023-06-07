#include "../../include/interpreter.h"
/* The interpreter passes on a queue (FIFO) linked list to the parser
of type t_token *token; a token can be either a WORD or OPERATOR
 The aim of this function here is to create the data structure struct s_simple_command; and ?? Compund_commands*/


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
};

	i = 0;
	while (array_of_operands[i])
	{
		if (!ft_strncmp(array_of_operands[i], token, ft_strlen(array_of_operands[i])))
			return (true);
	}
	return (false);
}

static void set_type(t_token *first)
{
	t_token	*temp;

	temp = first;
	while (temp)
	{
		if(is_operand(temp->token))
			temp->identifier = OPR;
		else
			temp->identifier = WRD;
		temp = temp->next;
	}
}

/*  */
t_token	*parse(char *input)
{
	/* First in queue */
	t_token				*first;
	// t_simple_command	*sc;

	first = tkn_queue(input);
	/* assert token que is properly functioning */
	set_type(first);

	//!here
	return first;

}

#ifdef TEST_ALL
int main(int argc, char **argv) {

	int i = 0;
	for (char *test_case = INPUT_TEST[i]; test_case; i++, test_case = INPUT_TEST[i])
	{
		t_token *token_queue_ll = parse(test_case);
		printf("Test case no: %d\n", i + 1);
		printf("(%s)\n", test_case);
		for (t_token *temp = token_queue_ll; temp; temp = temp->next)
		{
			printf("%s", temp->token);
			printf(", type: %s\n", temp->identifier == OPR? "OPR":"WORD");
		}
		printf("______________________________\n");
	}
}
#endif
