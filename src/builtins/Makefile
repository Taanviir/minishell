# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/16 22:46:50 by tanas             #+#    #+#              #
#    Updated: 2023/10/09 18:12:50 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
BLUE_I:= "\033[3;34m"
RESET:= "\033[0m"

NAME:= builtins.a
C_FLAGS:= -Wall -Werror -Wextra
INCLUDES:= -I ../../include -I ../../libft/include

SRCS:= builtins.c ft_cd.c ft_unset.c ft_export.c ft_echo.c \
		ft_exit.c env_utils.c print_env_list.c
OBJS_DIR:= builtins_objs/
OBJS:= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $@ $^
	@echo $(GREEN_B)"Builtins is ready. ✅\n"$(RESET)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $^ -o $@
	@echo $(BLUE_I)"Compiling src/builtins/$<."$(RESET)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

debug : C_FLAGS += -g3
debug : re

.PHONY : all clean fclean re debug
