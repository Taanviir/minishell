### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m
### DIRS
ERR_DIR:= ../src/error

UTILS_DIR:= ../src/utils

SRCS_DIR:= ../src
###

CC_FLAGS:= -Wall -Werror -Wextra -std=c99 -ggdb3

SRCS:=

OBJS:= $(SRCS:.c=.o)

NAME:= minishell

all: $(NAME)
	+$(MAKE) -C $(ERR_DIR)
	+$(MAKE) -C $(UTILS_DIR)
	+$(MAKE) -C $(SRCS_DIR)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "$(COLOR_GREEN)>>library ready$(COLOR_END)"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_RED)full clean completed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
