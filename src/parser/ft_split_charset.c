/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:31:54 by rverhoev          #+#    #+#             */
/*   Updated: 2023/10/05 16:31:56 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*split_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	substr = (char *)malloc(sizeof(char) * len);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static int	nbr_of_words(char *s, const char *set)
{
	int	nbr_of_c;
	int	i;

	i = 0;
	nbr_of_c = 0;
	if (*s == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (!ft_strchr(set, s[i]))
		{
			while (!ft_strchr(set, s[i]) && s[i] != '\0')
				i++;
			nbr_of_c++;
		}
		else
			i++;
	}
	return (nbr_of_c);
}

static void	*free_all(char **str_arr, int i)
{
	while (i >= 0)
	{
		free(str_arr[i]);
		str_arr[i] = 0;
		i--;
	}
	free(str_arr);
	str_arr = 0;
	return (NULL);
}

static char	**splitting(char **str_arr, char *s, const char *set, int nbr_of)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	j = 0;
	i = 0;
	while (j < nbr_of)
	{
		while (ft_strchr(set, s[i]))
			i++;
		while (!ft_strchr(set, s[i - len]) && s[i + len] != '\0')
			len++;
		str_arr[j] = split_substr(s, i, len + 1);
		if (str_arr[j] == NULL)
			return (free_all(str_arr, nbr_of));
		i = i + len;
		len = 0;
		j++;
	}
	str_arr[nbr_of] = NULL;
	return (str_arr);
}

char	**ft_split_charset(const char *s, const char *set)
{
	char	**str_arr;
	int		word_cnt;

	word_cnt = (nbr_of_words((char *)s, set));
	if (!(word_cnt == 0))
	{
		str_arr = (char **)malloc(sizeof(char *) * (word_cnt + 1));
		splitting(str_arr, (char *)s, set, word_cnt);
		if (str_arr == NULL)
			return (NULL);
	}
	if (word_cnt == 0)
	{
		str_arr = (char **)malloc(sizeof(char *) * 1);
		if (str_arr == NULL)
			return (NULL);
		str_arr[0] = NULL;
	}
	return (str_arr);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (0);
// 	printf("%s\n", argv[1]);
// 	char **split = ft_split_charset(argv[1], " \t\v\f\r");
// 	for (int i = 0; split[i]; i++)
// 		printf("%s\n", split[i]);
// 	for (int i = 0; split[i]; i++)
// 		free(split[i]);
// 	free(split);
// 	return (0);
// }
