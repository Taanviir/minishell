# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/06/28 21:53:16 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
RED_BI:= "\033[1;3;31m"
BLUE_I:= "\033[3;34m"
COLOUR_RESET:= "\033[0m"

NAME:= parser.a
C_FLAGS:= -Wall -Werror -Wextra -ggdb3
INCLUDES:= -I ../../include -I ../../libft/include
LIBFT:= ../../libft/libft.a

SRCS:= get_token.c parser.c queue.c expansion.c
OBJS_DIR:= obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@ar -rcs $@ $^

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/parser/$<."$(COLOUR_RESET)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all test fclean clean re
