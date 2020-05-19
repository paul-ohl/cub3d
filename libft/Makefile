SRCS		= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_strchr.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
				ft_tolower.c ft_toupper.c ft_atoi.c ft_memset.c ft_bzero.c \
				ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
				ft_calloc.c ft_strdup.c ft_strlcpy.c ft_strlcat.c ft_substr.c \
				ft_strtrim.c ft_strjoin.c ft_itoa.c ft_split.c ft_strmapi.c \
				ft_putstr_fd.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				get_next_line.c is_whitespace.c ft_atoi_increment.c ft_intlen.c\
				ft_strcmp.c

SRCS_BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

OBJ_DIR		= obj
SRC_DIR		= src
INC_DIR		= .

OBJS		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_BONUS	:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_BONUS))

NAME		= libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJS) $(OBJS_BONUS)
	@echo "Compiling libft."
	@ar rc $(NAME) $(OBJS) $(OBJS_BONUS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	$(RM) -r $(OBJ_DIR)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

bonus:			$(OBJS) $(OBJS_BONUS)
	ar rc $(NAME) $(OBJS) $(OBJS_BONUS)

.PHONY:	all clean clean re bonus
