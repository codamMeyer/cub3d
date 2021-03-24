/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:19:08 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/15 21:03:12 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s);
	c = (unsigned char)c;
	ptr = (char *)s;
	while (i >= 0)
	{
		if (ptr[i] == c)
			return (&ptr[i]);
		--i;
	}
	return (NULL);
}
