#include "../../include/tokenizer.h"
#include "../../include/tokenizer/type.h"


/* define TEST_ALL if you want to test all*/

char const whitespace[] = " \t\r\n\v";
char const operators[]="<|>&;()";

/* checks if a char is an operator if its returns the operator
c has to be a pointer because it needs to move to check for >>
'+' for >>
'a' for anything thats not an operator
! change function name
*/
static char find_type(char **s)
{
	int	i;

	while (not_whitespace(**s))
	{
		i = 0;
		while (operators[i])
		{
			if (!**s)
				return (0);
			else if (**s == '>' && **(s + 1) == '>')
			{
				*s += 2;
				return ('+');
			}
			if (!**s)
				return (0);
			else if (**s == operators[i])
			{
				**s += 1;
				return (**s);
			}
			i++;
		}
		*s += 1;
	}
	return ('a');
}
/* Returns false if it is a white space, also false if its a null */
static bool not_whitespace(char c)
{
	int	i;

	i = 0;
	while (whitespace[i]) {
		if (!c || c == whitespace[i])
			return (false);
		i++;
	}
	return (true);
}

char get_token(char **input_command, char *token_end,
char **q, char **eq)
{
	char	ret;
	char	*s;

	s = *input_command; /* storing the original start of the string */
	while (s < token_end && not_whitespace(*s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	ret = find_type(&s);
	if (eq)
		*eq = s;
	/* skip white spaces */
	while (!not_whitespace(*s))
		s++;
	*input_command = s;
	return (ret);
}


#ifdef TEST_ALL
int main(int argc, char **argv)
{
	int i = 0;
	for (char *test_case = INPUT_TEST[i]; test_case; i++, test_case = INPUT_TEST[i])
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

