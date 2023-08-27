# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 14:38:29 by tanas             #+#    #+#              #
#    Updated: 2023/08/21 18:10:57 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS
GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
YELLOW = "\033[0;33m"
RESET = "\033[0m"

NAME = minishell
C_FLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I include/ -I libft/include -I /usr/local/opt/readline/include
LIBFT = libft/libft.a
PARSER = src/parser/parser.a
BUILTINS = src/builtins/builtins.a
EXECUTION = src/execution/execution.a
FREE = src/free/free.a
LD =   $(PARSER) $(EXECUTION) $(BUILTINS) $(FREE) $(LIBFT) -lreadline -L /usr/local/opt/readline/lib

SRCS_DIR = src/
SRCS_LIST = main.c signal.c environment.c wrappers.c utils.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = obj/
OBJS_LIST = $(SRCS_LIST:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)

$(NAME) : $(LIBFT) libraries $(OBJS)
	@$(CC) $(C_FLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LD)
	@echo $(GREEN_B)"$(NAME) is ready. ✅\n"$(RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@echo $(BLUE_I)"Compiling $<."$(RESET)

$(LIBFT) :
	@echo $(YELLOW)"Creating $(LIBFT)"$(RESET)
	@make -sC libft
	@echo $(GREEN_B)"\nLibft is ready. ✅\n"$(RESET)

run : $(NAME)
	clear
	./$(NAME)

libraries :
	@make -sC src/parser
	@make -sC src/builtins
	@make -sC src/execution
	@make -sC src/free

clean :
	@rm -rf $(NAME)
	@make clean -sC libft
	@make clean -sC src/parser
	@make clean -sC src/builtins
	@make clean -sC src/execution
	@make clean -sC src/free
	@rm -rf $(OBJS_DIR)
	@echo $(RED_BI)"\nRemoving all object directories and files"$(RESET)

fclean : clean
	@make fclean -sC libft
	@make fclean -sC src/parser
	@make fclean -sC src/builtins
	@make fclean -sC src/execution
	@make fclean -sC src/free
	@echo $(RED_BI)"Removing $(NAME) and all libraries\n"$(RESET)

re : fclean all

.PHONY : all clean fclean re libraries
