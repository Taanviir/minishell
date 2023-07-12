# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 02:10:11 by sabdelra          #+#    #+#              #
#    Updated: 2023/07/13 02:43:27 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS
GREEN_B:= "\033[1;32m"
RED_BI:= "\033[1;3;31m"
BLUE_I:= "\033[3;34m"
COLOUR_RESET:= "\033[0m"

C_FLAGS:= -Wall -Werror -Wextra -ggdb3
INCLUDES:= -I ../include -I ../libft/include
LIBFT:= ../libft/libft.a

SRCS:= echo.c export.c pwd.c
BIN_DIR:= bin
BINS = $(addprefix $(BIN_DIR)/, $(notdir $(SRCS:.c=)))

all: $(BINS)

$(BIN_DIR)/%: %.c
	@mkdir -p $(BIN_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) $^ -o $@ $(LIBFT)

clean:
	@rm -rf bin

fclean: clean

re: fclean all

.PHONY: all clean fclean re
