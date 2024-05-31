/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 14:27:10 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/11 12:29:27 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// static void	ft_printlist(t_list *lst)
// {
// 	while (lst != 0)
// 	{
// 		printf("%s\n", (char *)lst->content);
// 		lst = lst->next;
// 	}
// }

// int	main(void)
// {
// 	t_list	*new;

// 	new = ft_lstnew("1");
// 	ft_lstadd_front(&new, ft_lstnew("2"));
// 	ft_printlist(new);
// }
