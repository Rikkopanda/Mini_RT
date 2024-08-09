NAME = minirt

# CFLAGS = -Wall -Wextra -Werror
# CFLAGS := -fsanitize=address
CFLAGS += -Ofast
# CFLAGS += -fPIE
CFLAGS += -g

CC = cc

DIR_LIB = lib
LINKS = -L${DIR_LIB}/libft -lft -L${DIR_LIB}/get_next_line -lgnl 

LINKS_MLX = -L${DIR_LIB}/minilibx-linux -lmlx -lX11 -lXext -lm -lz

INCLUDE = -I./include -I./${DIR_LIB}/minilibx-linux -I./${DIR_LIB}/libft -I./${DIR_LIB}/get_next_line

MLX_LIB = ${DIR_LIB}/minilibx-linux/libmlx.a


LIBFT = ${DIR_LIB}/libft/libft.a
LIBGNL = ${DIR_LIB}/get_next_line/libgnl.a

DIR_SRC = src
DIR_PARSER = parser
DIR_PARSER_OBJECTS = objects
DIR_PARSER_GETTERS = getters_setters
DIR_PARSER_INTERSECTS = intersects
DIR_OBJ = obj

DIR_RENDERER = renderer

RAYS_N = 45
MAX_BOUNCE_DEPTH = 3

CFLAGS += -DREFLECT_RAYS_N=$(RAYS_N)
CFLAGS += -DMAX_BOUNCE_DEPTH=$(MAX_BOUNCE_DEPTH)

SRC = main.c

SRC_PARSER =	parser.c ft_2darray_size.c ft_atovec3f.c ft_atof.c \
				ft_split_charset.c ft_str_endswith.c object_list.c \
				ft_min_max.c ft_rgb_to_int.c ft_free_2darray.c \
				clamped_rgb_to_int.c ft_vec_in_range.c parse_object.c swapf.c
SRC_PARSER_OBJECTS =	parse_ambient.c parse_camera.c parse_cylinder.c \
						parse_light.c parse_plane.c parse_sphere.c
SRC_PARSER_OBJECTS := ${addprefix ${DIR_PARSER_OBJECTS}/, ${SRC_PARSER_OBJECTS}}
SRC_PARSER_GETTERS =	sphere_get_set.c light_get_set.c plane_get_set.c cylinder_get_set.c print_data.c \
						assign_geometric_get_set.c assign_material_get_set.c
SRC_PARSER_GETTERS := ${addprefix ${DIR_PARSER_GETTERS}/, ${SRC_PARSER_GETTERS}}
SRC_PARSER_INTERSECTS = sphere_intersect.c light_intersect.c plane_intersect.c cylinder_intersect.c
SRC_PARSER_INTERSECTS := ${addprefix ${DIR_PARSER_INTERSECTS}/, ${SRC_PARSER_INTERSECTS}}
SRC_PARSER := ${addprefix ${DIR_PARSER}/, ${SRC_PARSER} ${SRC_PARSER_OBJECTS} ${SRC_PARSER_GETTERS} ${SRC_PARSER_INTERSECTS}}

SRC_RENDERER =	render_scene.c matrixes.c matrix_tools.c \
	send_rays.c vector_functions.c \
	colors_drawing.c hooks.c ft_mlx_functions.c \
	trace_ray.c check_intersection.c
SRC_RENDERER := ${addprefix ${DIR_RENDERER}/, ${SRC_RENDERER}}

SRC := ${addprefix ${DIR_SRC}/, ${SRC} ${SRC_PARSER} ${SRC_RENDERER}}

OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

${NAME}: ${OBJ} | ${MLX_LIB} ${LIBFT} ${LIBGNL}
	$(CC) ${CFLAGS} $^ ${LINKS} ${LINKS_MLX} -o $@

${MLX_LIB}:
	make -C ${DIR_LIB}/minilibx-linux

${LIBFT}:
	make -C ${DIR_LIB}/libft

${LIBGNL}:
	make -C ${DIR_LIB}/get_next_line

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@mkdir -p ${@D}
	$(CC) ${CFLAGS} ${INCLUDE} -c $< -o $@

all: ${NAME}

debug: CFLAGS += -g
debug: re

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

tests: ${OBJ}
	@make run_tests -C tests IS_INCLUDED=1

re: fclean all

.PHONY: all clean fclean re tests debug
