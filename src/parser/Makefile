# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/10/09 18:13:34 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
BLUE_I:= "\033[3;34m"
RESET:= "\033[0m"

NAME:= parser.a
C_FLAGS:= -Wall -Werror -Wextra
INCLUDES:= -I ../../include -I ../../libft/include

SRCS:= get_token.c parser.c expansion.c constructor.c here_doc.c \
		parse_exec.c parse_redir.c nulterminate.c here_doc_utils.c
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

debug : C_FLAGS += -g3
debug : re

.PHONY : all fclean clean re debug
