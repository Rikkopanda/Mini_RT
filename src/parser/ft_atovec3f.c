#include "../../include/minirt.h"

t_vec4f	atovec3f(const char *a_vec3f)
{
	t_vec4f	vec4;
	char	**split;

	ft_bzero(&vec4, sizeof(vec4));
	split = ft_split(a_vec3f, ',');
	if (!split)
		return (perror("malloc error"), vec4);
	if (ft_2darray_size(split) != 3)
		return (ft_free_2darray(split), vec4);
	vec4[0] = ft_atof(split[0]);
	vec4[1] = ft_atof(split[1]);
	vec4[2] = ft_atof(split[2]);
	ft_free_2darray(split);
	return (vec4);
}
