# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/06/18 18:17:13 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= parser.a

### COLORS
GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
COLOUR_RESET = "\033[0m"

INC_DIR:= ../../include

C_FLAGS:= -Wall -Werror -Wextra -ggdb3

SRCS:= tokenizer.c parser.c queue.c

# OBJS_DIR:= obj/
# OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS:= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $@ $^

%.o : %.c
	@mkdir obj/
	@$(CC) $(C_FLAGS) -I $(INC_DIR) -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/parser/$<."$(COLOUR_RESET)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY = all test fclean clean re
