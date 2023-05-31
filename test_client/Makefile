### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m
### DIRS
TOK_DIR:=../src/tokenizer

GNL_DIR:=../src/gnl
### LIB
TOK_LIB:=../src/tokenizer/tokenizer

GNL_LIB:=../src/gnl/gnl

UTILS:=../src/utils/utils
###

CC_FLAGS:= -Wall -Werror -Wextra -std=c99 -ggdb3

NAME:= minishell

all: $(NAME)

libs:
	+$(MAKE) -C $(TOK_DIR)
	+$(MAKE) -C $(GNL_DIR)

$(NAME): libs
	$(CC) $(CC_FLAGS) main.c $(TOK_LIB) $(GNL_LIB) $(UTILS) -o $@ 
	@echo "$(COLOR_GREEN)>>minishell ready$(COLOR_END)"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	+$(MAKE) -C $(TOK_DIR) fclean
	+$(MAKE) -C $(GNL_DIR) fclean
	@echo "$(COLOR_RED)full clean completed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
