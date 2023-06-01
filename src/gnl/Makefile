### COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m

CC:= gcc

SRC:= get_next_line.c get_next_line_utils.c

OBJ:= $(SRC:.c=.o)

NAME:= gnl

CC_FLAGS:= -Wall -Werror -Wextra -O3

all: $(NAME)


$(NAME): $(OBJ)
	@ar crs $@ $^
	@echo "$(COLOR_BLUE)>>gnl ready$(COLOR_END)"

fclean: clean
	@rm $(NAME)
	@echo "$(COLOR_GREEN)>>gnl removed$(COLOR_END)"

clean:
	@rm $(OBJ)

re: fclean all

.PHONY: all clean re fclean main