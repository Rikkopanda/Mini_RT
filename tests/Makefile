ifndef IS_INCLUDED
$(error This Makefile cannot be run directly)
endif

NAME_PARSER = ${DIR_BIN}/parser_tests
PROGRAM = ../minirt

CFLAGS = -Wall -Wextra -Werror

DIR_LIB = lib
INCLUDE = -I../include -I../${DIR_LIB}/libft -I../${DIR_LIB}/get_next_line

LINKS = -L../${DIR_LIB}/libft -lft -L../${DIR_LIB}/get_next_line -lgnl

DIR_SRC = ../src
DIR_OBJ = ../obj

OBJ = ${shell find ${DIR_OBJ}/parser -name "*.o"}
OBJ := ${filter-out ${DIR_OBJ}/main.o, ${OBJ}}

ifeq ($(OBJ),)
$(error OBJ is empty)
endif

DIR_OBJ_TESTS = obj
DIR_SRC_TESTS = .
SRC_TESTS = ${addprefix ${DIR_SRC_TESTS}/, main_parser.c debug_info.c}
OBJ_TESTS = ${subst ${DIR_SRC_TESTS}/, ${DIR_OBJ_TESTS}/, ${SRC_TESTS:.c=.o}}
DIR_BIN = bin

all: ${NAME_PARSER}

run_tests: parser

${OBJ_TESTS}: ${DIR_OBJ_TESTS}/%.o: ${DIR_SRC_TESTS}/%.c
	@mkdir -p ${@D}
	cc ${CFLAGS} ${INCLUDE} -c $< -o $@

parser: ${NAME_PARSER}
	./test_parser.bash

${NAME_PARSER}: ${OBJ} ${OBJ_TESTS}
	@mkdir -p ${@D}
	cc ${CFLAGS} $^ ${LINKS} ${LINKS_MLX} -o $@

clean:
	rm -f ${OBJ_TESTS}

fclean: clean
	rm -f ${NAME_PARSER}

re: fclean all

.PHONY: all parser clean fclean re run_tests
