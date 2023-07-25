# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 14:38:29 by tanas             #+#    #+#              #
#    Updated: 2023/07/25 21:45:23 by sabdelra         ###   ########.fr        #
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
INCLUDES = -I include/ -I libft/include -I test/
LIBFT = libft/libft.a
PARSER = src/parser/parser.a
BUILTINS = src/builtins/builtins.a

TESTER = test/test.a

LD = -lreadline $(PARSER) $(BUILTINS) $(LIBFT)

SRCS_DIR = src/
SRCS_LIST = main.c signal.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = obj/
OBJS_LIST = $(SRCS_LIST:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)

test : C_FLAGS += -D TEST
test : $(LIBFT) $(OBJS) libraries
	@$(CC) $(C_FLAGS) $(INCLUDES) $(OBJS) -o test_shell $(LD) $(TESTER)
	@echo $(GREEN_B)"$(NAME) (Test Build) is ready. ✅\n"$(RESET)

$(NAME) : $(LIBFT) $(OBJS) libraries
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

libraries :
	@make -sC src/parser
	@make -sC src/builtins
	@make -sC test

clean :
	@make clean -sC test
	@make clean -sC libft
	@make clean -sC src/parser
	@make clean -sC src/builtins
	@rm -rf $(OBJS_DIR)
	@echo $(RED_BI)"\nRemoving all object directories and files"$(RESET)

fclean : clean
	@rm -f $(NAME) test_shell
	@make fclean -sC test
	@make fclean -sC libft
	@make fclean -sC src/parser
	@make fclean -sC src/builtins
	@echo $(RED_BI)"Removing $(NAME) and all libraries\n"$(RESET)

re : fclean all

.PHONY : all clean fclean re libraries
