/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:19:17 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/13 11:20:47 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		cmp_with_set(char c, const char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int		find_start(char const *s1, char const *set)
{
	int start;

	start = 0;
	while (cmp_with_set(s1[start], set))
		++start;
	return (start);
}

static int		find_end(char const *s1, char const *set)
{
	int			end;
	const int	s1_len = ft_strlen(s1);

	end = s1_len - 1;
	while (cmp_with_set(s1[end], set) && end > 0)
		--end;
	return (end);
}

static int		calc_new_str_len(char const *s1, char const *set, int *start)
{
	const int end = find_end(s1, set);

	*start = find_start(s1, set);
	if (*start == (int)ft_strlen((char *)s1))
		return (0);
	else
		return (end - *start + 1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		new_len;
	char	*new_str;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	new_len = calc_new_str_len(s1, set, &start);
	new_str = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < new_len && new_len != 0)
	{
		new_str[i] = s1[start + i];
		i++;
	}
	return (new_str);
}
