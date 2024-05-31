/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 15:47:29 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 17:10:25 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
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
// 	ft_lstadd_back(&new, ft_lstnew("2"));
// 	ft_printlist(new);
// }
