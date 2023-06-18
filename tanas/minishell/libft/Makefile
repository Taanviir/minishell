NAME 		= libft.a
C_FLAGS 	= -Wall -Wextra -Werror

SRC_PATH 	= sources
OBJ_PATH 	= objects
SUB_DIRS 	= error-utils ft_printf get_next_line is-utils linked-list memory-utils put-utils string-utils to-utils

OBJS_DIRS 	= $(foreach directory, $(SUB_DIRS), $(addprefix $(OBJ_PATH)/, $(directory))) # adding the prefix objects/ to each subdirectory
SRCS 		= $(SRC_PATH)/error-utils/ft_error.c \
			$(SRC_PATH)/ft_printf/ft_print_char.c $(SRC_PATH)/ft_printf/ft_print_hex.c $(SRC_PATH)/ft_printf/ft_print_number.c $(SRC_PATH)/ft_printf/ft_print_pointer.c \
			$(SRC_PATH)/ft_printf/ft_print_string.c $(SRC_PATH)/ft_printf/ft_print_unsigned.c $(SRC_PATH)/ft_printf/ft_printf.c \
			$(SRC_PATH)/get_next_line/get_next_line.c \
			$(SRC_PATH)/is-utils/ft_isalnum.c $(SRC_PATH)/is-utils/ft_isalpha.c $(SRC_PATH)/is-utils/ft_isascii.c $(SRC_PATH)/is-utils/ft_isdigit.c $(SRC_PATH)/is-utils/ft_isprint.c \
			$(SRC_PATH)/linked-list/ft_lstadd_back.c $(SRC_PATH)/linked-list/ft_lstadd_front.c $(SRC_PATH)/linked-list/ft_lstclear.c $(SRC_PATH)/linked-list/ft_lstdelone.c \
			$(SRC_PATH)/linked-list/ft_lstiter.c $(SRC_PATH)/linked-list/ft_lstlast.c $(SRC_PATH)/linked-list/ft_lstmap.c $(SRC_PATH)/linked-list/ft_lstnew.c $(SRC_PATH)/linked-list/ft_lstsize.c \
			$(SRC_PATH)/memory-utils/ft_bzero.c $(SRC_PATH)/memory-utils/ft_calloc.c $(SRC_PATH)/memory-utils/ft_memchr.c $(SRC_PATH)/memory-utils/ft_memcmp.c $(SRC_PATH)/memory-utils/ft_memcpy.c \
			$(SRC_PATH)/memory-utils/ft_memmove.c $(SRC_PATH)/memory-utils/ft_memset.c $(SRC_PATH)/memory-utils/free_double_ptr.c \
			$(SRC_PATH)/put-utils/ft_putchar_fd.c $(SRC_PATH)/put-utils/ft_putendl_fd.c $(SRC_PATH)/put-utils/ft_putnbr_fd.c $(SRC_PATH)/put-utils/ft_putstr_fd.c \
			$(SRC_PATH)/string-utils/ft_split.c $(SRC_PATH)/string-utils/ft_strchr.c $(SRC_PATH)/string-utils/ft_strdup.c $(SRC_PATH)/string-utils/ft_striteri.c $(SRC_PATH)/string-utils/ft_strjoin.c \
			$(SRC_PATH)/string-utils/ft_strlcat.c $(SRC_PATH)/string-utils/ft_strlcpy.c $(SRC_PATH)/string-utils/ft_strlen.c $(SRC_PATH)/string-utils/ft_strmapi.c $(SRC_PATH)/string-utils/ft_strncmp.c \
			$(SRC_PATH)/string-utils/ft_strnstr.c $(SRC_PATH)/string-utils/ft_strrchr.c $(SRC_PATH)/string-utils/ft_strtrim.c $(SRC_PATH)/string-utils/ft_substr.c \
			$(SRC_PATH)/to-utils/ft_atoi_base.c $(SRC_PATH)/to-utils/ft_atoi.c $(SRC_PATH)/to-utils/ft_itoa.c $(SRC_PATH)/to-utils/ft_tolower.c $(SRC_PATH)/to-utils/ft_toupper.c
OBJS 		= $(subst $(SRC_PATH), $(OBJ_PATH), $(SRCS:.c=.o)) # changing .c to .o for object files

YELLOW 		= "\033[0;33m"
RESET	 	= "\033[0m"

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $(NAME) $^

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) $(OBJS_DIRS)
	@cc $(C_FLAGS) -I includes -c $< -o $@
	@echo $(YELLOW)".\c"$(RESET)

clean :
	@rm -rf $(OBJS) $(OBJ_PATH)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY = all clean fclean re