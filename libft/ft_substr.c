/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:19:23 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/14 17:29:07 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_substr_len(size_t s_len, unsigned int start, size_t max_len)
{
	size_t substr_len;

	if (start >= s_len)
		return (0);
	substr_len = s_len - start;
	if (max_len < substr_len)
		substr_len = max_len;
	return (substr_len);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	substr_len;
	char	*substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_len = (size_t)ft_strlen(s);
	substr_len = get_substr_len(s_len, start, len);
	substr = (char *)ft_calloc(substr_len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < substr_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr);
}
