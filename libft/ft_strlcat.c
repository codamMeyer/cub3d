/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 17:12:57 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/09 17:43:20 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const size_t	dest_len = ft_strlen(dst);
	const size_t	src_len = ft_strlen(src);
	const size_t	max_to_append = (size - 1);
	size_t			i;

	i = 0;
	if (size == 0)
		return (src_len);
	if (size <= dest_len)
		return (src_len + size);
	while ((src[i] != '\0') && ((dest_len + i) < max_to_append))
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	if (size > dest_len)
		return (dest_len + src_len);
	return (size + src_len);
}
