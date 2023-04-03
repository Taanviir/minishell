#include "../../../include/token.h"
#include <stdio.h>


int	main(int argc, char **argv, char **envp)
{
	t_token *token = mk_token(argv[1], envp);
	printf("token: %s has type: %d\n", token->s_token, token->type);
	free_token(token);
}
