NAME = libgnl.a

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fPIE

SRC = get_next_line.c get_next_line_utils.c

SRC_BONUS = get_next_line_bonus.c get_next_line_utils_bonus,c

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	ar rcs ${NAME} ${OBJ}

clean:
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

bonus: ${NAME} ${OBJ_BONUS}
	ar rcs ${NAME} ${OBJ_BONUS}

.PHONY: all clean fclean re bonus