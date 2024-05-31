/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 15:41:27 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 16:59:54 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*new;

// 	new = ft_lstnew("4");
// 	ft_lstadd_front(&new, ft_lstnew("3"));
// 	ft_lstadd_front(&new, ft_lstnew("2"));
// 	ft_lstadd_front(&new, ft_lstnew("1"));
// 	printf("%s\n", (char *)ft_lstlast(new)->content);
// }
