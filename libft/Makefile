# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 16:13:46 by tanas             #+#    #+#              #
#    Updated: 2023/10/09 18:13:41 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS
YELLOW = "\033[0;33m"
RESET = "\033[0m"

NAME = libft.a
C_FLAGS = -Wall -Wextra -Werror

SRCS_DIR = src/
SRCS_LIST = error-utils/ft_error.c \
			ft_printf/ft_print_char.c ft_printf/ft_print_hex.c ft_printf/ft_print_number.c ft_printf/ft_print_pointer.c \
			ft_printf/ft_print_string.c ft_printf/ft_print_unsigned.c ft_printf/ft_printf.c \
			get_next_line/get_next_line.c \
			is-utils/ft_is_alnum.c is-utils/ft_is_alpha.c is-utils/ft_is_ascii.c is-utils/ft_is_digit.c is-utils/ft_is_print.c is-utils/ft_is_whitespace.c\
			linked-list/ft_lstadd_back.c linked-list/ft_lstadd_front.c linked-list/ft_lstclear.c linked-list/ft_lstdelone.c \
			linked-list/ft_lstiter.c linked-list/ft_lstlast.c linked-list/ft_lstmap.c linked-list/ft_lstnew.c linked-list/ft_lstsize.c \
			memory-utils/ft_bzero.c memory-utils/ft_calloc.c memory-utils/ft_memchr.c memory-utils/ft_memcmp.c memory-utils/ft_memcpy.c \
			memory-utils/ft_memmove.c memory-utils/ft_memset.c memory-utils/free_double_ptr.c \
			put-utils/ft_putchar_fd.c put-utils/ft_putendl_fd.c put-utils/ft_putnbr_fd.c put-utils/ft_putstr_fd.c \
			string-utils/ft_split.c string-utils/ft_strchr.c string-utils/ft_strdup.c string-utils/ft_striteri.c string-utils/ft_strjoin.c \
			string-utils/ft_strlcat.c string-utils/ft_strlcpy.c string-utils/ft_strlen.c string-utils/ft_strmapi.c string-utils/ft_strncmp.c \
			string-utils/ft_strnstr.c string-utils/ft_strrchr.c string-utils/ft_strtrim.c string-utils/ft_substr.c \
			to-utils/ft_atoi_base.c to-utils/ft_atoi.c to-utils/ft_itoa.c to-utils/ft_tolower.c to-utils/ft_toupper.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
SUB_DIRS = error-utils ft_printf get_next_line is-utils linked-list memory-utils put-utils string-utils to-utils

OBJS_DIR = obj/
OBJS_SUBDIRS = $(foreach directory, $(SUB_DIRS), $(addprefix $(OBJS_DIR), $(directory))) # adding the prefix objects/ to each subdirectory
OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o)) # changing .c to .o for object files

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $(NAME) $^

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR) $(OBJS_SUBDIRS)
	@$(CC) $(C_FLAGS) -I include -c $< -o $@
	@echo $(YELLOW)".\c"$(RESET)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

debug : C_FLAGS += -g3
debug : re

.PHONY : all clean fclean re debug
