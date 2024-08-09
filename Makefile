NAME = minirt

CFLAGS = -Wall -Wextra -Werror
# CFLAGS := -fsanitize=address
CFLAGS += -Ofast
# CFLAGS += -fPIE
# CFLAGS := -g

CC = cc

DIR_LIB = lib
LINKS = -L${DIR_LIB}/libft -lft -L${DIR_LIB}/get_next_line -lgnl 

LINKS_MLX = -L${DIR_LIB}/minilibx-linux -lmlx -lX11 -lXext -lm -lz

INCLUDE = -I./include -I./src/renderer/math -I./${DIR_LIB}/minilibx-linux -I./${DIR_LIB}/libft -I./${DIR_LIB}/get_next_line

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
DIR_MATH = math
DIR_HOOKS = hooks

REFL_RAYS_N = 45
MAX_BOUNCE_DEPTH = 3

CFLAGS += -DREFL_RAYS_N=$(REFL_RAYS_N)
CFLAGS += -DMAX_BOUNCE_DEPTH=$(MAX_BOUNCE_DEPTH)

SRC = main.c parser.c ft_2darray_size.c ft_atovec3f.c ft_atof.c \
		ft_split_charset.c ft_str_endswith.c object_list.c \
		ft_min_max.c ft_rgb_to_int.c ft_free_2darray.c clamped_rgb_to_int.c \
		ft_vec_in_range.c parse_object.c \
		parse_ambient.c parse_camera.c parse_cylinder.c \
		parse_light.c parse_plane.c parse_sphere.c \
		render_scene.c matrixes.c matrix_tools_1.c matrix_tools_2.c \
		send_rays.c vector_functions_1.c vector_functions_2.c \
		hooks.c ft_mlx_functions.c math_tools.c \
		trace_ray.c check_intersection.c std_color_functions_1.c \
		std_color_functions_2.c quaternion_functions.c orient_ray_coordinates.c \
		random_vec_gen.c hooks_action_rotate.c hooks_action_move.c \
		trace_ray_helpers.c vector_functions_3.c \
		sphere_get_set.c plane_get_set.c cylinder_get_set.c light_get_set.c \
		assign_geometric_get_set.c assign_material_get_set.c print_data.c \
		cylinder_intersect.c plane_intersect.c sphere_intersect.c light_intersect.c \
		swapf.c


vpath %.c ${DIR_SRC}
vpath %.c ${DIR_SRC}/${DIR_PARSER}
vpath %.c ${DIR_SRC}/${DIR_PARSER}/${DIR_PARSER_INTERSECTS}
vpath %.c ${DIR_SRC}/${DIR_PARSER}/${DIR_PARSER_OBJECTS}
vpath %.c ${DIR_SRC}/${DIR_PARSER}/${DIR_PARSER_GETTERS}
vpath %.c ${DIR_SRC}/${DIR_RENDERER}
vpath %.c ${DIR_SRC}/${DIR_RENDERER}/${DIR_HOOKS}
vpath %.c ${DIR_SRC}/${DIR_RENDERER}/$(DIR_MATH)

OBJ = ${notdir ${SRC:.c=.o}}

KAAS:
	$(foreach LIBDIR, $(shell find lib -maxdepth 1 -mindepth 1 -d -print), $(MAKE) -C $(LIBDIR);)

${NAME}: ${OBJ} | ${MLX_LIB} ${LIBFT} ${LIBGNL}
	$(CC) ${CFLAGS} $^ ${LINKS} ${LINKS_MLX} -o $@

${MLX_LIB}:
	make -C ${DIR_LIB}/minilibx-linux

${LIBFT}:
	make -C ${DIR_LIB}/libft

${LIBGNL}:
	make -C ${DIR_LIB}/get_next_line

${OBJ}: %.o: %.c
	@mkdir -p ${@D}
	$(CC) ${CFLAGS} ${INCLUDE} -c $< -o $@

all: ${NAME}

debug: CFLAGS += -g
debug: re

print: CFLAGS += -DPRINT_STATUS
print: re

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

tests: ${OBJ}
	@make run_tests -C tests IS_INCLUDED=1

re: fclean all

.PHONY: all clean fclean re tests debug KAAS
