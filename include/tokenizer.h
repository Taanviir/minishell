/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:59:44 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/02 07:20:55 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

bool	is_ws(char c);
bool	is_opr(char c);
char	get_token(char **b_start, char *b_end, char **q, char **eq);
char	*expand(char *q, char **envp);

extern char	*INPUT_TEST[102];


# endif
