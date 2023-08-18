# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/08/18 19:22:05 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
BLUE_I:= "\033[3;34m"
RESET:= "\033[0m"

NAME:= parser.a
C_FLAGS:= -Wall -Werror -Wextra -ggdb3
INCLUDES:= -I ../../include -I ../../libft/include

SRCS:= get_token.c parser.c expansion.c constructor.c here_doc.c parse_exec.c parse_redir.c
OBJS_DIR:= parser_objs/
OBJS:= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $@ $^
	@echo $(GREEN_B)"Parser is ready. ✅\n"$(RESET)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/parser/$<."$(RESET)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all test fclean clean re
