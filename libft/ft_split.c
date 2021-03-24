/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:18:28 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/23 10:21:38 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_mem(char **splits, int i)
{
	while (i >= 0)
	{
		free(splits[i]);
		i--;
	}
	free(splits);
}

static char	**split(char **splits, const char *str, int n_splits, char c)
{
	int i;
	int cur_len;

	i = 0;
	while (i < n_splits)
	{
		cur_len = 0;
		while (str[cur_len] == c)
			str++;
		while (str[cur_len] != c && str[cur_len] != '\0')
			cur_len++;
		splits[i] = (char*)malloc(cur_len + 1 * sizeof(char));
		if (splits[i] == NULL)
		{
			free_mem(splits, i - 1);
			return (NULL);
		}
		ft_memcpy(splits[i], str, cur_len);
		splits[i][cur_len] = '\0';
		str = &str[cur_len];
		i++;
	}
	if (n_splits != 0)
		splits[i] = NULL;
	return (splits);
}

static int	num_of_splits(char const *str, char c)
{
	int i;
	int num_of_splits;

	i = 0;
	num_of_splits = 0;
	if (str[0] != c && str[0] != '\0')
		num_of_splits++;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			num_of_splits++;
		i++;
	}
	return (num_of_splits);
}

char		**ft_split(char const *s, char c)
{
	char	**split_strs;
	int		n_of_splits;

	if (s == NULL)
		return (NULL);
	n_of_splits = num_of_splits(s, c);
	split_strs = (char**)malloc((n_of_splits + 1) * sizeof(char*));
	if (split_strs == NULL)
		return (NULL);
	if (n_of_splits == 0 || s[0] == '\0')
	{
		split_strs[0] = NULL;
		return (split_strs);
	}
	split_strs = split(split_strs, s, n_of_splits, c);
	return (split_strs);
}
