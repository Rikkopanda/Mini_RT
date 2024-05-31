/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 14:41:31 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 15:40:43 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != 0)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*new;

// 	new = ft_lstnew("4");
// 	ft_lstadd_front(&new, ft_lstnew("3"));
// 	ft_lstadd_front(&new, ft_lstnew("2"));
// 	ft_lstadd_front(&new, ft_lstnew("1"));
// 	printf("lst size: %d\n", ft_lstsize(new));
// }
