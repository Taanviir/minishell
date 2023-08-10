#include "minishell.h"

static t_exec *inc_argsize(t_exec *cmd, size_t argc) {
	t_exec *ret;

	ret = ft_calloc(sizeof(t_exec), 1);
	ret->expanded = ft_calloc(sizeof(bool), (argc + ARGC));
	ret->argv = ft_calloc(sizeof(char *), (argc + ARGC));
	ret->eargv = ft_calloc(sizeof(char *), (argc + ARGC));
	ft_memcpy(ret, cmd, sizeof(cmd));
	ft_memcpy(ret->argv, cmd->argv, sizeof(char *) * argc);
	ft_memcpy(ret->eargv, cmd->eargv, sizeof(char *) * argc);
	free(cmd->argv);
	free(cmd->eargv);
	free(cmd);
	return (ret);
}

/* check the type of token returned to determine if its expandable and if
	its a valid token */
static bool check_token(char **q, char **eq, int *token)
{
	if (!token)
		return (false);
	else if (!ft_strchr("aq", token))
	{
		write(2, "syntax", 7);
		return (false);
	}
	else if (token == 'q')
	{
		if (*q == '\'')
			*token = 'n';
		*q += 1;
		*eq -= 1;
		*token = 'e';
	}
	else if (*q == '$')
		*token = 'e';
	return (true);
}



t_cmd *parseexec(char **b_start, char *b_end, char **envp)
{
	char	*q;
	char	*eq;
	int		token;
	t_exec	*cmd;
	t_cmd	*ret;

	ret = construct_exec();
	cmd = (t_exec *)ret;
	ret = parseredir(ret, b_start, b_end, envp);
	while (!peek(b_start, b_end, "|&;"))
	{
		token = get_token(b_start, b_end, &q, &eq);
		if (!check_token(&q, &eq, &token))
			break ;
		if (token == 'e')
		{
			cmd->argv[cmd->argc] = expand(q, eq, envp);

			if (cmd->argv[cmd->argc]) // avoid double free if this returned null
				cmd->expanded[cmd->argc] = true;
			else if ((!cmd->argv[cmd->argc] && token == 'q'))
				cmd->argv[cmd->argc] = strdup(" ");

			cmd->eargv[cmd->argc] = cmd->argv[cmd->argc] + ft_strlen(cmd->argv[cmd->argc]);
		}
		else
		{
		cmd->argv[cmd->argc] = q;
		cmd->eargv[cmd->argc] = eq;
		}
		// *************** clean this shit up ***************************************//
		if (cmd->argv[cmd->argc]) // this condition to avoid nulling too early if expand returned null
		cmd->argc++;
		if (cmd->argc > (ARGC - 1)) //! wrong ARGC doesn't update
		cmd = inc_argsize(cmd, cmd->argc);
		ret = parseredir(ret, b_start, b_end, envp);
	}
	cmd->argv[cmd->argc] = 0;
	cmd->eargv[cmd->argc] = 0;
	return (ret);
}
