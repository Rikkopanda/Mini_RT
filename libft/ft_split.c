/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 20:35:59 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/18 14:50:45 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static size_t	total_strings_to_split(char const *s, char c)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i] != 0)
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (s[i] == 0)
			break ;
		size++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (size);
}

static char	**split_strings(char const *s, char c, int split_size)
{
	char	**split;
	int		split_index;
	int		i;
	int		start;

	split = ft_calloc(split_size + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	split_index = 0;
	while (split_index < split_size)
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (s[i] == 0)
			break ;
		start = i;
		while (s[i] != c && s[i] != 0)
			i++;
		split[split_index++] = ft_substr(s, start, i - start);
		if (split[split_index - 1] == NULL)
			return (free_all(split), NULL);
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		split_size;

	if (s == NULL)
		return (NULL);
	split_size = total_strings_to_split(s, c);
	if (split_size == 0)
		return (NULL);
	split = split_strings(s, c, split_size);
	if (split == NULL)
		return (NULL);
	return (split);
}

// #include <unistd.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char const	src[] = " asdh  kjashd j hsdh j  shs";
// 	char		**temp;
// 	int			i;

// 	temp = ft_split(src, ' ');
// 	i = 0;
// 	while (temp[i] != 0)
// 	{
// 		printf("ft_split: %s\n", temp[i]);
// 		i++;
// 	}
// 	printf("ft_split: %s\n", temp[i]);
// 	free_all(temp);
// }
