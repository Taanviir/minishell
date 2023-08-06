/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eva-1 <eva-1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:19:12 by eva-1             #+#    #+#             */
/*   Updated: 2023/08/06 19:03:51 by eva-1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

t_cmd *parseexec(char **b_start, char *b_end, char **envp);

/* str is a string of characters to look for
this functions is used to deteremine which parse
function to call */
int peek(char **b_start, char *b_end, const char *str) {
  char *s;

  s = *b_start;
  while (s < b_end && ft_is_whitespace(*s))
    s++;
  *b_start = s;
  return (*s && ft_strchr(str, *s));
}

//! error here exit properly */
t_cmd *parseredir(t_cmd *cmd, char **b_start, char *b_end) {
  int redirection;
  int hc_pipe[2];
  char *q;
  char *eq;
  char *del;

  while (peek(b_start, b_end, "<>")) {
    redirection = get_token(b_start, b_end, 0, 0);
    if (redirection == '-') {
      if (!pipe(hc_pipe)) {
        cmd = construct_redircmd(cmd, 0, (char *)&hc_pipe[0], O_RDONLY, STDIN_FILENO);
        if (get_token(b_start, b_end, &q, &eq) == 'a') // quotes and expansion case != 'q'
          del = get_del(q, eq);
        else // no del case
          del = 0;
        here_doc(hc_pipe[1], del);
        if (del)
          free(del);
        close(hc_pipe[1]); // don't close read end, still needed during execution
      }
      // else pipe error
    } else if (get_token(b_start, b_end, &q, &eq) != 'a')
      write(2, "no file", 8);
    else if (redirection == '<')
      cmd = construct_redircmd(cmd, q, eq, O_RDONLY, STDIN_FILENO);
    else if (redirection == '>')
      cmd = construct_redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC,
                               STDOUT_FILENO);
    else if (redirection == '+')
      cmd = construct_redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND,
                               STDOUT_FILENO);
  }
  return (cmd);
}

//! heredoc if unclosed pipe
t_cmd *parsepipe(char **b_start, char *b_end, char **envp) {
  t_cmd *cmd;

  cmd = parseexec(b_start, b_end, envp);
  if (peek(b_start, b_end, "|")) {
    get_token(b_start, b_end, 0, 0);
    if (*b_start == b_end) {
      write(2, "syntax error near unexpected token `|'\n", 39);
    }
    cmd = construct_pipecmd(cmd, parsepipe(b_start, b_end, envp));
  }
  return (cmd);
}

//! heredoc if unclosed pipe
t_cmd *parseline(char **b_start, char *b_end, char **envp) {
  t_cmd *cmd;

  cmd = parsepipe(b_start, b_end, envp);
  while (peek(b_start, b_end, "&")) {
    get_token(b_start, b_end, 0, 0);
    if (*b_start == b_end) {
      write(2, "syntax error near unexpected token `&'\n", 39);
    }
    cmd = construct_bgcmd(cmd);
  }
  while (peek(b_start, b_end, ";")) {
    get_token(b_start, b_end, 0, 0);
    if (*b_start == b_end) {
      write(2, "syntax error near unexpected token `;'\n", 39);
    }
    cmd = construct_seqcmd(cmd, parseline(b_start, b_end, envp));
  }
  return (cmd);
}

static t_exec *inc_argsize(t_exec *cmd, size_t argc) {
  t_exec *ret;

  ret = ft_calloc(sizeof(t_exec), 1);
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

//! fix exit
t_cmd *parseexec(char **b_start, char *b_end, char **envp) {
  char *q;
  char *eq;
  int token;
  size_t argc;
  t_exec *cmd;
  t_cmd *ret;

  argc = 0;
  ret = construct_exec();
  cmd = (t_exec *)ret;
  ret = parseredir(ret, b_start, b_end);
  while (!peek(b_start, b_end, "|&;")) {
    token = get_token(b_start, b_end, &q, &eq);
    if (!token)
      break;
    if (token == 'q') {
      q += 1;
      eq -= 1;
    }
    if (token != 'a' && token != 'q')
      write(2, "syntax", 7);
    if (*q == '$' || *q == '\"' || *q == '\'') {
      cmd->argv[argc] = expand(q, eq, envp);
      cmd->eargv[argc] = cmd->argv[argc] + ft_strlen(cmd->argv[argc]);
    } else {
      cmd->argv[argc] = q;
      cmd->eargv[argc] = eq;
    }
    argc++;
    if (argc > (ARGC - 1))
      cmd = inc_argsize(cmd, argc);
    ret = parseredir(ret, b_start, b_end);
  }
  cmd->argv[argc] = 0;
  cmd->eargv[argc] = 0;
  return (ret);
}

t_cmd *nullterminate(t_cmd *cmd) {
  t_exec *execmd;
  t_redircmd *redircmd;
  t_pipecmd *pipecmd;
  t_seqcmd *seqcmd;
  t_bgcmd *bgcmd;
  int i;

  if (!cmd)
    return (0);
  i = -1;
  if (cmd->type == EXEC) {
    execmd = (t_exec *)cmd;
    while (execmd->argv[++i])
      *execmd->eargv[i] = 0;
  } else if (cmd->type == REDIR) {
    redircmd = (t_redircmd *)cmd;
    nullterminate(redircmd->cmd);
    if (redircmd->fp) //! here_doc case
      *redircmd->efp = 0;
  } else if (cmd->type == PIPE) {
    pipecmd = (t_pipecmd *)cmd;
    nullterminate(pipecmd->left);
    nullterminate(pipecmd->right);
  } else if (cmd->type == SEQUENCE) {
    seqcmd = (t_seqcmd *)cmd;
    nullterminate(seqcmd->left);
    nullterminate(seqcmd->right);
  } else if (cmd->type == BG) {
    bgcmd = (t_bgcmd *)cmd;
    nullterminate(bgcmd->cmd);
  }
  return (cmd);
}

//! fix to adjust for exit, for now it only prints "SYNTAX MF" */
t_cmd *parsecmd(char *b_start, char **envp) {
  char *b_end;
  t_cmd *root;

  if (!b_start[0])
    return (free(b_start), NULL);
  b_end = ft_strlen(b_start) + b_start;
  root = parseline(&b_start, b_end, envp);
  if (peek(&b_start, b_end, ""))
    write(2, "SYNTAX MF\n", 11);
  nullterminate(root);
  return (root);
}
