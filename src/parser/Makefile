### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m
### DIRS
INC_DIR:= ../../include

UTILS_DIR:= ..//
### libs
UTILS:= $(UTILS_DIR)utils
###

CC_FLAGS:= -Wall -Werror -Wextra -std=c99 -ggdb3

SRCS:= tokenizer.c parser.c queue.c

OBJS:= tokenizer.o parser.o queue.o

NAME:= parser

all: $(NAME) clean

$(UTILS):
	$(MAKE) -C $(UTILS_DIR)

$(NAME): $(OBJS) $(UTILS)
	@ar rcs $@ $(UTILS) $^
	@echo "$(COLOR_BLUE)>>parser is up to date!$(COLOR_END)"

%.o: %.c
	@$(CC) $(CC_FLAGS) -c -I $(INC_DIR) $^ -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(UTILS_DIR) fclean
	@echo "$(COLOR_RED)parser removed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
