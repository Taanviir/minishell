# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/07/07 16:24:29 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
RED_BI:= "\033[1;3;31m"
BLUE_I:= "\033[3;34m"
COLOUR_RESET:= "\033[0m"

NAME:= parser.a
C_FLAGS:= -Wall -Werror -Wextra -ggdb3

SRCS:= get_token.c parser.c expansion.c constructor.c
OBJS_DIR:= obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

test: all test.c
	$(CC) $(C_FLAGS) -I ../../include test.c $(NAME) ../../libft/libft.a -o $@

ast: test
	./test > test.dot
	dot -Tpng test.dot > test.png
	@rm -f test.dot

$(NAME) : $(OBJS)
	@ar -rcs $@ $^

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) -I ../../include -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/parser/$<."$(COLOUR_RESET)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all test fclean clean re
