/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:15:27 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/10 14:59:46 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	const size_t	num_bites = nmemb * size;

	ptr = malloc(num_bites);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, num_bites);
	return (ptr);
}
