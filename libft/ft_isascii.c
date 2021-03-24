/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:27:18 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/09 17:22:44 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_isascii(int c)
{
	int first_ascii;
	int last_ascii;

	first_ascii = 0;
	last_ascii = 127;
	return (c >= first_ascii && c <= last_ascii);
}
