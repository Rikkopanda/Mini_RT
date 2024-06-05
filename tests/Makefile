NAME_PARSER = ${DIR_BIN}/parser_tests

CFLAGS = -Wall -Wextra -Werror

DIR_LIB = lib
LIBFT = ../${DIR_LIB}/libft/libft.a
LIBGNL = ../${DIR_LIB}/get_next_line/libgnl.a
INCLUDE = -I../include -I../${DIR_LIB}/libft -I../${DIR_LIB}/get_next_line

LINKS = -L../${DIR_LIB}/libft -lft -L../${DIR_LIB}/get_next_line -lgnl

DIR_PARSER = ../src/parser

SRC_PARSER =	ft_atof.c ft_chcount.c ft_split_charset.c object_parsing.c \
				parser.c sphere_format.c ft_str_endswith.c
SRC_PARSER := ${addprefix ${DIR_PARSER}/, ${SRC_PARSER}}

DIR_OBJ_PARSER = obj_tests/parser

OBJ_PARSER = ${subst ${DIR_PARSER}/, ${DIR_OBJ_PARSER}/, ${SRC_PARSER:.c=.o}}

DIR_BIN = bin

all: parser

${LIBFT}:
	make -C libft

${DIR_OBJ_PARSER}/main_parser.o: main_parser.c
	@mkdir -p ${@D}
	cc ${CFLAGS} ${INCLUDE} -c $< -o $@

parser: ${NAME_PARSER}
	${NAME_PARSER}

${NAME_PARSER}: ${OBJ_PARSER} ${DIR_OBJ_PARSER}/main_parser.o | ${LIBFT} ${LIBGNL}
	@mkdir -p ${@D}
	cc ${CFLAGS} $^ ${LINKS} -o $@

${OBJ_PARSER}: ${DIR_OBJ_PARSER}/%.o: ${DIR_PARSER}/%.c
	@mkdir -p ${@D}
	cc ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:
	rm -f ${OBJ_PARSER}

fclean: clean
	rm -f ${NAME_PARSER}

re: fclean all

.PHONY: all parser clean fclean re
