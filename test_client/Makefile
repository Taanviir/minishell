### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m
### DIRS
PRS_DIR:=../src/parser

GNL_DIR:=../src/gnl
### LIB
TOK_LIB:=../src/parser/parser

GNL_LIB:=../src/gnl/gnl

UTILS:=../src/utils/utils
###

CC_FLAGS:= -Wall -Werror -Wextra -std=c99 -ggdb3

NAME:= minishell

all: $(NAME)

libs:
	+$(MAKE) -C $(PRS_DIR)

$(NAME): libs
	$(CC) $(CC_FLAGS) main.c $(TOK_LIB) $(GNL_LIB) $(UTILS) -o $@
	@echo "$(COLOR_GREEN)>>minishell is up to date\n$(COLOR_END)"

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(PRS_DIR) fclean

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_RED)full clean completed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
