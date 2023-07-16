# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/07/13 22:31:15 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
BLUE_I:= "\033[3;34m"
COLOUR_RESET:= "\033[0m"

NAME:= parser.a
C_FLAGS:= -Wall -Werror -Wextra -ggdb3
INCLUDES:= -I ../../include -I ../../libft/include
LIBFT:= ../../libft/libft.a
LD:= -lreadline $(LIBFT)

SRCS:= get_token.c parser.c expansion.c constructor.c
OBJS_DIR:= obj/
OBJS:= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

test : all test/test.c
	$(CC) $(C_FLAGS) $(INCLUDES) test/test.c $(NAME) -o test/testfile $(LD)

### tree diagram
ast : test
	./test/testfile $(index) > test/test.dot
	dot -Tpng test/test.dot > test/test.png

cleanast :
	@rm -f test/test.png test/testfile test/test.dot

$(NAME) : $(OBJS)
	@ar -rcs $@ $^

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/parser/$<."$(COLOUR_RESET)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean cleanast
	@rm -f $(NAME)

re : fclean all

.PHONY : all test fclean clean re
