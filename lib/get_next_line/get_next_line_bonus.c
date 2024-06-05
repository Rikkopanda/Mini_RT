/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 12:50:44 by kwchu         #+#    #+#                 */
/*   Updated: 2023/11/27 16:30:04 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

static void	*ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (*s);
}

static char	*ft_splitline(char **leftover)
{
	char	*temp;
	char	*one_line;
	ssize_t	split;

	split = 0;
	while ((*leftover)[split] != '\0' && (*leftover)[split] != '\n')
		split++;
	one_line = gnl_substr(*leftover, 0, split + 1);
	if (one_line == NULL)
		return (ft_free(leftover));
	temp = *leftover;
	*leftover = gnl_substr(temp, split + 1, BUFFER_SIZE);
	free(temp);
	return (one_line);
}

static char	*ft_read_newline(int fd, char *buffer, char **leftover)
{
	ssize_t	bytes;
	char	*temp;

	if (gnl_strchr(*leftover, '\n'))
		return (ft_splitline(leftover));
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == -1)
		return (ft_free(leftover));
	buffer[bytes] = 0;
	while (bytes > 0)
	{
		temp = *leftover;
		*leftover = gnl_strjoin(temp, buffer);
		free(temp);
		if (*leftover == NULL)
			return (NULL);
		if (gnl_strchr(buffer, '\n'))
			return (ft_splitline(leftover));
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = 0;
	}
	if (**leftover == 0)
		return (ft_free(leftover));
	return (ft_splitline(leftover));
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*one_line;
	static char	*leftover[65536];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (leftover[fd] == NULL)
		leftover[fd] = gnl_strdup("");
	if (leftover[fd] == NULL)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	one_line = ft_read_newline(fd, buffer, &leftover[fd]);
	ft_free(&buffer);
	if (one_line == NULL)
		return (NULL);
	return (one_line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int	fd = open("./read.txt", O_RDONLY);

// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		// printf("gnl: %s\n", line);
// 		free(line);
// 		line =	get_next_line(fd);
// 	}
// 	// printf("getnextline: %s\n", get_next_line(fd));
// 	// printf("getnextline: %s\n", get_next_line(fd));
// 	// printf("getnextline: %s\n", get_next_line(fd));
// 	// printf("getnextline: %s\n", get_next_line(fd));
// 	// printf("getnextline: %s\n", get_next_line(fd));
// 	// printf("getnextline: %s\n", get_next_line(fd));
// 	// printf("getnextline: %s\n", get_next_line(fd));
// 	// printf("getnextline: %s\n", get_next_line(fd));
// }
