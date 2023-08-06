/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eva-1 <eva-1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:52:34 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/06 19:38:46 by eva-1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>

// remove its the same as tanvir
static int get_len(char *str1, char *str2) {
  int length1;
  int length2;

  length1 = ft_strlen(str1);
  length2 = ft_strlen(str2);
  if (length1 > length2)
    return (length1);
  return (length2);
}

// gets the delimeter from get_token, q and eq
char *get_del(char *q, char *eq) {
  char *del;
  int i;

  i = 0;
  del = malloc(sizeof(char) * (eq - q) + 1);
  if (!del)
    perror("malloc failed in get_del");
  while (q < eq) {
    del[i] = *q;
    q++;
    i++;
  }
  del[i] = 0;
  return (del);
}

void here_doc(int fd, char *del) {
  char *line;

  while (true) {
    line = readline(">"); 
    if (!line || (del && !ft_strncmp(del, line, get_len(del, line)))) {
      free(line);
      break;
    }
    write(fd, line, ft_strlen(line));
    write(fd, "\n", 1);
    free(line);
  }
}

// int main(void) {
// 	char *q, *eq;
// 	char *str = "01234Hello77123";
// 	q = str + 5;
// 	eq = str + 10;

// 	printf("%s\n",get_del(q, eq));
// }
