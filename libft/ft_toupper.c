/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:29:37 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/13 11:19:41 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int		is_lower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int				ft_toupper(int c)
{
	const int offset = 32;

	if (is_lower(c))
		return (c - offset);
	return (c);
}
