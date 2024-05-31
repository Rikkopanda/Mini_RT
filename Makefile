NAME = minirt

CFLAGS = -Wall -Wextra -Werror

LINKS = -Llibft -lft

LINKS_MLX = -Lminilibx-linux -lmlx

INCLUDE = -I./include -I./minilibx-linux -I./libft

MLX_LIB = minilibx-linux/libmlx.a

LIBFT = libft/libft.a

DIR_SRC = src
DIR_PARSER = parser
DIR_OBJ = obj

SRC = main.c
SRC_PARSER = parser.c
SRC_PARSER := ${addprefix ${DIR_PARSER}/, ${SRC_PARSER}}

SRC := ${addprefix ${DIR_SRC}/, ${SRC} ${SRC_PARSER}}

OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

${NAME}: ${OBJ} ${MLX_LIB}
	cc ${CFLAGS} $< ${LINKS} ${LINKS_MLX} -o $@

${MLX_LIB}:
	make -C minilibx-linux

${LIBFT}:
	make -C libft

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@mkdir -p ${@D}
	cc ${CFLAGS} ${INCLUDE} -c $< -o $@

all: ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
