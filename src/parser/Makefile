# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/06/18 15:20:25 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= parser.a

### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
BLUE_I = "\033[3;34m"
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m

### DIRS
INC_DIR:= ../../include

CC_FLAGS:= -Wall -Werror -Wextra -ggdb3

SRCS:= tokenizer.c parser.c queue.c

OBJS:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@ar rcs $@ $(LIBFT) $^

%.o: %.c
	@$(CC) $(CC_FLAGS) -c -I $(INC_DIR) $^ -o $@
	@echo $(BLUE_I)"Compiling $<."$(COLOUR_END)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(COLOR_RED)parser removed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
