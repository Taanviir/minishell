#include "../../include/token.h"

/*
	ARG,	// argument
	OPR,	// operator
	VAR,	// variable
	QTS,	// quotes
	BSL		// backslash
 */

static bool	is_command(t_token *token, char **envp);
static char	**get_path(char **envp);

void	set_token_type(t_token *token, char **envp)
{
	if (is_command(token, envp))
		token->type = CMD;
}

/* static bool	is_operator(t_token *token)
{
	(void)token;
	return (false);
} */

static bool	is_command(t_token *token, char **envp)
{
	char	**path_array;
	char	*path_command;
	int		command_size;
	int		i;

	i = 0;
	path_array = get_path(envp); // array of $(PATH) directories
	while (path_array[i])
	{
		command_size = ft_strlen(path_array[i]) + ft_strlen(token->name) + 2; // (null) and (/)
		path_command = ft_calloc(sizeof(char), command_size);
		ft_strcat(path_command, path_array[i]);
		ft_strcat(path_command, "/");
		ft_strcat(path_command, token->name);
		if (!access(path_command, X_OK))
		{
			free(path_command);
			return (true);
		}
		free(path_command);
		i++;
	}
	free_split(path_array);
	return (false);
}

static char	**get_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	return (path);
}
