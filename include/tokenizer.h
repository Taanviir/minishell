/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:25:28 by tanas             #+#    #+#             */
/*   Updated: 2023/08/22 00:03:07 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define ARGC 20

# define EXEC 0
# define REDIR 1
# define PIPE 2
# define SEQUENCE 3
# define BG 4

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_exec
{
	int		type;
	size_t	argc;
	char	**argv;
	char	**eargv;
}	t_exec;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*fp;
	char	*efp;
	int		here_doc;
	int		mode;
	int		fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_seqcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_seqcmd;

typedef struct s_bgcmd
{
	int		type;
	t_cmd	*cmd;
}	t_bgcmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/* open conditions */
enum e_open_conditions
{
	MODE,
	FD
};

/* tokenizers */
char	get_token(char **bs, char *be, char **ts, char **te);
char	*expand(char *q, char *eq, t_env **env_list, bool here_doc);
int		peek(char **b_start, char *b_end, const char *str);
/* parsers */
t_cmd	*parseredir(t_cmd *cmd, char **b_start, char *b_end, t_env **env_list);
t_cmd	*parseexec(char **b_start, char *b_end, t_env **env_list);
t_cmd	*parsecmd(char *b_start, t_env **env_list);
t_cmd	*nullterminate(t_cmd *cmd);
/* constructors */
t_cmd	*construct_exec(void);
t_cmd	*construct_redircmd(t_cmd *cmd, char *fp, char *efp, int *oc);
t_cmd	*construct_pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*construct_seqcmd(t_cmd *left, t_cmd *right);
t_cmd	*construct_bgcmd(t_cmd *cmd);
/* here_document */
void	here_doc(const int fd, char *del, t_env **env_list);
char	*get_delimiter(char *q, const char *eq);

// execution
void	execute_cmd(t_cmd *cmd, t_env **env_list);
void	execute_redir(t_cmd *cmd, t_env **env_list);
void	execute_pipe(t_cmd *cmd, t_env **env_list);

#endif
