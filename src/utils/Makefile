### Makes utils and errors

### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m
###

###

CC_FLAGS:= -Wall -Werror -Wextra -std=c99 -ggdb3

INC_DIR:= ../../include

ERR_DIR:= ../error

SRCS:= queue.c ft_strlen.c ft_strlcpy.c \
		ft_strncmp.c ft_strcat.c ft_calloc.c ft_memset.c\
		$(ERR_DIR)/mem_error.c

OBJS:= queue.o ft_strlen.o ft_strlcpy.o \
		ft_strncmp.o ft_strcat.o ft_calloc.o ft_memset.o\
		$(ERR_DIR)/mem_error.o

NAME:= utils

all: $(NAME) clean

### testing
testsplit: ./test/test_split.c all
	@$(CC) $< $(NAME) -I $(INC_DIR) -o $@ -ggdb3
	@echo "$(COLOR_BLUE)>>testsplit is ready$(COLOR_END)"

### end

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "$(COLOR_BLUE)>>utils is up to date!$(COLOR_END)"

%.o: %.c
	@$(CC) $(CC_FLAGS) -c -I $(INC_DIR) $^ -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f testsplit
	@echo "$(COLOR_RED)utils removed$(COLOR_END)"

re: fclean all

.PHONY: all test fclean clean re
