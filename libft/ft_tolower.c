/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:29:00 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/13 11:19:29 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static	int		is_upper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int				ft_tolower(int c)
{
	const int offset = 32;

	if (is_upper(c))
		return (c + offset);
	return (c);
}
