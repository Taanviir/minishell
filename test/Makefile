# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 10:35:41 by tanas             #+#    #+#              #
#    Updated: 2023/07/20 13:35:06 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS
GREEN_B = "\033[1;32m"
BLUE_I = "\033[3;34m"
RESET = "\033[0m"

NAME = test.a
C_FLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I ../include/ -I ../libft/include
LIBFT = ../libft/libft.a

SRCS = test.c print_root.c

OBJS_DIR = test_objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $@ $^
	@echo $(GREEN_B)"Test.png is ready. ✅\n"$(RESET)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@echo $(BLUE_I)"Compiling $<."$(RESET)

clean :
	@rm -rf $(OBJS_DIR)
	@rm -f test.dot test.png

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
