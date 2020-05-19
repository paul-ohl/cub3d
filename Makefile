SRCS		= display.c ray.c utils.c parser.c readers.c map_reader.c \
				check_map.c bmp_creator.c error_handler.c movement_handler.c

SRCS_BONUS	=

LIBS		= libft

OBJ_DIR		= objs
SRC_DIR		= srcs

OBJS		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_BONUS	:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_BONUS))
DEP			:= $(patsubst %.o,%.d,$(OBJS))
DEP			+= $(patsubst %.o,%.d,$(OBJS_BONUS))

NAME		= cub3D
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -Ofast -g3
LDFLAGS		= -lm -lXext -lX11 -lmlx
INCLUDES	:= -I . $(patsubst %,-I %,$(LIBS))

all: 			$(NAME)
	@$(foreach L, $(LIBS), $(MAKE) -C $L -j;)

$(NAME):		$(OBJS) $(foreach L,$(LIBS),$L/$L.a)
	@mkdir -p "imgs/screenshots"
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

-include $(DEP)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCLUDES)

libft/libft.a:
	@$(MAKE) -C libft


libmlx/libmlx.a:
	@$(MAKE) -C libmlx

clean:
	@$(foreach L, $(LIBS), $(MAKE) -C $L clean;)
	$(RM) -r $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME) $(foreach L,$(LIBS),$L/$L.a)
	$(RM) -r $(OBJ_DIR)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re libft libmlx
