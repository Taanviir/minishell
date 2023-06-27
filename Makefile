# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 14:38:29 by tanas             #+#    #+#              #
#    Updated: 2023/06/26 16:25:15 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
C_FLAGS = -Wall -Wextra -Werror -g3
LIBFT = libft/libft.a
LD_FLAGS = -lreadline $(LIBFT) src/parser/parser.a
INCLUDES = -Iinclude/ -Ilibft/include

SRCS_DIR = src/
SRCS_LIST = main.c signal.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = obj/
OBJS_LIST = $(SRCS_LIST:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

### COLOURS
GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
YELLOW = "\033[0;33m"
COLOUR_RESET = "\033[0m"

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS) parser
	@cc $(C_FLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LD_FLAGS)
	@echo $(GREEN_B)"$(NAME) is ready. ✅\n"$(COLOUR_RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@echo $(BLUE_I)"Compiling $<."$(COLOUR_RESET)

$(LIBFT) :
	@echo $(YELLOW)"Creating $(LIBFT)"$(COLOUR_RESET)
	@make -sC libft
	@echo $(GREEN_B)"\nLibft is ready. ✅\n"$(COLOUR_RESET)

parser :
	@make -sC src/parser

clean :
	@make clean -sC libft
	@make clean -sC src/parser
	@rm -rf $(OBJS_DIR)
	@echo $(RED_BI)"\nRemoving object directories and files"$(COLOUR_RESET)

fclean : clean
	@rm -f $(NAME)
	@make fclean -sC libft
	@make fclean -sC src/parser
	@echo $(RED_BI)"Removing $(NAME) and libft.a\n"$(COLOUR_RESET)

re : fclean all

.PHONY : all clean fclean re
