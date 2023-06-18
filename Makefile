# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 14:38:29 by tanas             #+#    #+#              #
#    Updated: 2023/06/18 14:53:15 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
C_FLAGS = -Wall -Wextra -Werror -g3
LIBFT = libft/libft.a
LD_FLAGS = -lreadline $(LIBFT)
INCLUDES = -Iinclude/ -Ilibft/includes

SRCS_DIR = src/
SRCS_LIST = main.c signal.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = obj/
OBJS_LIST = $(SRCS_LIST:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

# colours
GREEN = "\033[1;32m"
RED = "\033[1;3;31m"
BLUE = "\033[3;34m"
YELLOW = "\033[0;33m"
COLOUR_RESET = "\033[0m"

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@cc $(C_FLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LD_FLAGS)
	@echo $(GREEN)"$(NAME) is ready. ✅\n"$(COLOUR_RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@echo $(BLUE)"Compiling $<."$(COLOUR_RESET)

$(LIBFT) :
	@echo $(YELLOW)"Creating $(LIBFT)"$(COLOUR_RESET)
	@make -sC libft
	@echo $(GREEN)"\nLibft is ready. ✅\n"$(COLOUR_RESET)

parser :
	@make -sC src/parser
	@echo "parser is ready"

clean :
	@make clean -sC libft
	@rm -rf $(OBJS_DIR)
	@echo $(RED)"\nRemoving object directory and files"$(COLOUR_RESET)

fclean : clean
	@rm -f $(NAME)
	@make fclean -sC libft
	@echo $(RED)"Removing $(NAME), libft.a and libmlx.a\n"$(COLOUR_RESET)

re : fclean all

.PHONY = all clean fclean re
