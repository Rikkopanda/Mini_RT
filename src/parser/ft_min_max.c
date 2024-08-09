/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_min_max.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:06:48 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:06:49 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
