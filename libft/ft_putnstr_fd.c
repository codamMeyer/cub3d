/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnstr_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 19:07:20 by mmeyer        #+#    #+#                 */
/*   Updated: 2021/01/29 11:57:36 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(const char *s, int fd, int len)
{
	if (s == NULL || fd < 0)
		return ;
	write(fd, s, len);
}
