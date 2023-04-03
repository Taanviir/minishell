#include "../../include/token.h"

//* token is created its inserted into the que using the enqueue function(queue API)
t_token	*mk_token(char *s_token, char **envp)
{
	t_token	*token;
	size_t	s_len;

	token = malloc(sizeof(t_token));
	mem_error(token);
	s_len = ft_strlen(s_token);
	token->s_token = malloc(s_len + 1);
	ft_strlcpy(token->s_token, s_token, s_len);
	token->next = NULL;
	set_token_type(token, envp);
	return (token);
}

// * frees token and s_token (string token)
void	free_token(t_token *token)
{
	if (token)
	{
		free(token->s_token);
		free(token);
	}
}

