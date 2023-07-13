# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 02:10:11 by sabdelra          #+#    #+#              #
#    Updated: 2023/07/13 05:13:48 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
RED_BI:= "\033[1;3;31m"
BLUE_I:= "\033[3;34m"
COLOUR_RESET:= "\033[0m"

NAME:= builtins.a
C_FLAGS:= -Wall -Werror -Wextra -ggdb3
INCLUDES:= -I ../include -I ../libft/include
LIBFT:= ../libft/libft.a

SRCS:= echo.c
OBJSDIR:= obj
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

all: $(NAME)

test: all test.c
	$(CC) $(C_FLAGS) $(INCLUDES) test.c $(NAME) $(LIBFT) -o $@

$(NAME) : $(OBJS)
	@ar -rcs $@ $^

$(OBJSDIR)/%.o: %.c
	@mkdir -p $(OBJSDIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $^ -o $@
	@echo $(GREEN_B)"Compiling builtins/$<."$(COLOUR_RESET)

clean:
	@rm -rf $(OBJSDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f test

re: fclean all

.PHONY: all clean fclean re test
