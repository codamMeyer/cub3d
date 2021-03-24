/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:19:04 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/13 11:18:30 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s2[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	length_little;
	char	*big_pos;
	char	*little_pos;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	length_little = ft_strlen((char *)little);
	while (big[i] != '\0' && len >= length_little)
	{
		if (big[i] == little[0])
		{
			big_pos = (char *)&big[i];
			little_pos = (char *)&little[0];
			if (ft_cmp(big_pos, little_pos))
				return (big_pos);
		}
		len--;
		i++;
	}
	return (NULL);
}
