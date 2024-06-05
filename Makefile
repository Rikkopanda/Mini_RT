NAME = minirt

CFLAGS = -Wall -Wextra -Werror

DIR_LIB = lib
LINKS = -L${DIR_LIB}/libft -lft -L${DIR_LIB}/get_next_line -lgnl

LINKS_MLX = -L${DIR_LIB}/minilibx-linux -lmlx

INCLUDE = -I./include -I./${DIR_LIB}/minilibx-linux -I./${DIR_LIB}/libft -I./${DIR_LIB}/get_next_line

MLX_LIB = ${DIR_LIB}/minilibx-linux/libmlx.a

LIBFT = ${DIR_LIB}/libft/libft.a
LIBGNL = ${DIR_LIB}/get_next_line/libgnl.a

DIR_SRC = src
DIR_PARSER = parser
DIR_OBJ = obj

SRC = main.c
SRC_PARSER = parser.c ft_atof.c ft_chcount.c ft_split_charset.c ft_str_endswith.c object_list.c

SRC_PARSER := ${addprefix ${DIR_PARSER}/, ${SRC_PARSER}}

SRC := ${addprefix ${DIR_SRC}/, ${SRC} ${SRC_PARSER}}

OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

${NAME}: ${OBJ} | ${MLX_LIB} ${LIBFT}
	cc ${CFLAGS} $^ ${LINKS} ${LINKS_MLX} -o $@

${MLX_LIB}:
	make -C ${DIR_LIB}/minilibx-linux

${LIBFT}:
	make -C ${DIR_LIB}/libft

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@mkdir -p ${@D}
	cc ${CFLAGS} ${INCLUDE} -c $< -o $@

all: ${NAME}

debug: CFLAGS += -g
debug: re

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
