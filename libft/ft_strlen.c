/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:28:25 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/15 20:50:33 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen(const char *str)
{
	int length;

	length = 0;
	while (str[length] != '\0')
		++length;
	return (length);
}
