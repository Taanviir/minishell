# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/06/18 14:53:03 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= parser

### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m

### DIRS
INC_DIR:= ../../include

CC_FLAGS:= -Wall -Werror -Wextra -std=c99 -ggdb3

SRCS:= tokenizer.c parser.c queue.c

OBJS:= $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJS) $(LIBFT)
	@ar rcs $@ $(LIBFT) $^
	# @echo "$(COLOR_BLUE)>>parser is up to date!$(COLOR_END)"

%.o: %.c
	@$(CC) $(CC_FLAGS) -c -I $(INC_DIR) $^ -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(COLOR_RED)parser removed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
