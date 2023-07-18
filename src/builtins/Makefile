# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/16 22:46:50 by tanas             #+#    #+#              #
#    Updated: 2023/07/16 22:55:55 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
BLUE_I:= "\033[3;34m"
COLOUR_RESET:= "\033[0m"

NAME:= builtins.a
C_FLAGS:= -Wall -Werror -Wextra -ggdb3
INCLUDES:= -I ../include -I ../libft/include
LIBFT:= ../libft/libft.a
LIBFT:= ../../libft/libft.a
LD:= -lreadline $(LIBFT)

SRCS:= echo.c
OBJS_DIR:= builtin_objs/
OBJS:= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

test: all test.c
	$(CC) $(C_FLAGS) $(INCLUDES) test.c $(NAME) $(LIBFT) -o $@

$(NAME) : $(OBJS)
	@ar -rcs $@ $^
	@echo $(GREEN_B)"Builtins Ready. ✅\n"$(COLOUR_RESET)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/builtins/$<."$(COLOUR_RESET)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f test

re: fclean all

.PHONY: all clean fclean re test
