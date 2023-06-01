### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m
### DIRS
INC_DIR:= ../../include

ERR_DIR:= ../error/

UTILS_DIR:= ../utils/
### libs
UTILS:= $(UTILS_DIR)utils
###

CC_FLAGS:= -Wall -Werror -Wextra -std=c99 -ggdb3

SRCS:= queue.c set_token_type.c token.c

OBJS:= queue.o set_token_type.o token.o

NAME:= tokenizer

all: $(UTILS) $(NAME) clean

$(UTILS):
	$(MAKE) -C $(UTILS_DIR)

$(NAME): $(OBJS)
	@ar rcs $@ $(UTILS) $^
	@echo "$(COLOR_GREEN)>>tokenizer ready$(COLOR_END)"

%.o: %.c
	@$(CC) $(CC_FLAGS) -c -I $(INC_DIR) $^ -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(UTILS_DIR) fclean
	@echo "$(COLOR_RED)tokenizer clean completed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
