/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 13:54:50 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/15 20:49:04 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		str_cpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len_s1;
	int		len_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = (char *)ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (new_str == NULL)
		return (NULL);
	str_cpy(new_str, (char *)s1);
	str_cpy(&new_str[len_s1], (char *)s2);
	return (new_str);
}
