/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_2darray_size.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:07:06 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:07:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	ft_2darray_size(char **arr)
{
	size_t	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}
