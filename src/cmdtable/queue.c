// #include "../../include/cmdtable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct s_token
{
    char *t; // mallocd needs to be freed aswell
    struct s_token *next;
} t_token;


/* queue that is based on splitting up the user input into
tokens delimited by space or surrounded by "" or '' */
/* returns the head of a token queue the queue head is returned */
t_token *queue(char *input)
{

}

int main(int argc, char **argv)
{
	(void)argc;
	t_token *q;

	q = queue(argv[1]);
	for (t_token *temp = q; temp; temp = temp->next)
	{
		printf("%s\n", temp->t);
		printf("%d\n", 3);

	}
}
