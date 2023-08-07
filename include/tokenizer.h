/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:25:28 by tanas             #+#    #+#             */
/*   Updated: 2023/08/06 14:04:13 by tanas            ###   ########.fr       */
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
	char	**argv;
	char	**eargv;
}	t_exec;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*fp;
	char	*efp;
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


/* tokenizers */
char	get_token(char **buffer_start, char *buffer_end, char **token_start, char **token_end);
char	*expand(char *q, char *eq, char **envp);
int		peek(char **b_start, char *b_end, const char *str);
t_cmd	*parsecmd(char *b_start, char **envp);

/* constructors */
t_cmd	*construct_exec(void);
t_cmd	*construct_redircmd(t_cmd *command, char *fp, char *efp, int mode, int fd);
t_cmd	*construct_pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*construct_seqcmd(t_cmd *left, t_cmd *right);
t_cmd	*construct_bgcmd(t_cmd *cmd);

#endif
