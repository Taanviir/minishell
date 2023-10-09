# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:50:05 by sabdelra          #+#    #+#              #
#    Updated: 2023/10/09 18:13:05 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
BLUE_I:= "\033[3;34m"
RESET:= "\033[0m"

NAME:= execution.a
C_FLAGS:= -Wall -Werror -Wextra
INCLUDES:= -I ../../include -I ../../libft/include

SRCS:= execution.c execute_cmd.c execute_redir.c execute_pipe.c
OBJS_DIR:= execution_objs/
OBJS:= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $@ $^
	@echo $(GREEN_B)"Execution is ready. ✅\n"$(RESET)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/execution/$<."$(RESET)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

debug : C_FLAGS += -g3
debug : re

.PHONY : all fclean clean re debug
