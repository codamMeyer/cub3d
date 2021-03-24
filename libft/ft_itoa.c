/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:16:29 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/17 10:05:12 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len(long n)
{
	int len;

	len = 0;
	if (n <= 0)
	{
		++len;
		n *= -1;
	}
	while (n > 0)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static void		is_negative(long int *n, char *str)
{
	if (*n < 0 && *n * -1 > 0)
	{
		str[0] = '-';
		*n *= -1;
	}
}

char			*ft_itoa(int nb)
{
	char	*num_str;
	long	n;
	int		len;

	n = nb;
	len = ft_len(n);
	num_str = (char *)ft_calloc((len + 1), sizeof(char));
	if (num_str == NULL)
		return (NULL);
	len--;
	if (n == 0)
	{
		num_str[0] = '0';
		return (num_str);
	}
	if (n < 0)
		is_negative(&n, num_str);
	while (n > 0)
	{
		num_str[len] = '0' + (n % 10);
		n /= 10;
		len--;
	}
	return (num_str);
}
