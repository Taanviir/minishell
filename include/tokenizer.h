/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:59:44 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/02 07:20:55by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define ARGC 20
typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_exec
{
	int		type;
	char	**argv;
	char	**eargv;
}	 t_exec;

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

typedef struct	s_bgcmd
{
	int		type;
	t_cmd	*cmd;
}	t_bgcmd;

bool	is_ws(char c);
bool	is_opr(char c);
char	get_token(char **b_start, char *b_end, char **q, char **eq);
char	*expand(char *q, char **envp);
int		peek(char **b_start, char *b_end, const char *str);
t_cmd	*parsecmd(char *b_start);

extern char	*INPUT_TEST[102];


# endif
