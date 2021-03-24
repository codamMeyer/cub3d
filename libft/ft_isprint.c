/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:28:51 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/09 17:25:57 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprint(int c)
{
	const int first_printable = 32;
	const int last_printable = 127;

	return (c >= first_printable && c < last_printable);
}
