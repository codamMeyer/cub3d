/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:17:00 by mmeyer        #+#    #+#                 */
/*   Updated: 2020/11/14 16:57:36 by mmeyer        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	while (*lst != NULL)
	{
		temp = *lst;
		*lst = temp->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
