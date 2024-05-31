/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 15:17:11 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 12:55:42 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == 0 || f == 0)
		return ;
	while (s[i] != 0)
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// static void	ft_upper(unsigned int i, char *s)
// {
// 	if (i != 0)
// 		s[i] = s[i - 1] + 1;
// }

// int	main(void)
// {
// 	char	s[] = "0000000000";

// 	printf("before: %s\n", s);
// 	ft_striteri(s, ft_upper);
// 	printf("before: %s\n", s);
// }
