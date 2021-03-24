/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:17:36 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/15 20:31:12 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*copy_s;
	size_t			i;

	i = 0;
	copy_s = (unsigned char *)s;
	c = (unsigned char)c;
	while (i < n)
	{
		if (copy_s[i] == c)
			return (&copy_s[i]);
		++i;
	}
	return (NULL);
}
