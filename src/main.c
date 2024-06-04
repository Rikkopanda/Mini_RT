#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "parser.h"

// char	**ft_split_charset(const char *s, const char *set);

int	ft_str_endswith(const char *s, const char *end)
{
	int	len;
	int	i;

	if (s == end)
		return (1);
	if (!s || !end)
		return (0);
	len = ft_strlen(end) - 1;
	i = ft_strlen(s) - 1;
	if (len < 0 || i < 0 || i < len)
		return (0);
	while (len >= 0)
	{
		if (end[len] != s[i])
			return (0);
		len--;
		i--;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene_data	scene;
	int				fd;

	if (argc != 2)
	{
		printf("Usage: %s examplefile.rt\n", argv[0]);
		return (0);
	}
	if (!ft_str_endswith(argv[1], ".rt"))
	{
		printf("Error: %s: not an .rt file.\n", argv[1]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror(argv[1]), 1);
	if (!parse_rt_file(&scene, fd))
	{
		close(fd);
		return (1);
	}
	return (0);
}
