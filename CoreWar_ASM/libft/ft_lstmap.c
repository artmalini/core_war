/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:34:14 by amakhiny          #+#    #+#             */
/*   Updated: 2017/11/04 12:36:58 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*result;
	t_list		*head;
	t_list		*elem;

	if (!lst || !f)
		return (NULL);
	elem = f(lst);
	if (!(result = ft_lstnew(elem->content, elem->content_size)))
		return (NULL);
	lst = lst->next;
	head = result;
	while (lst != NULL)
	{
		elem = f(lst);
		if (!(result->next = ft_lstnew(elem->content, elem->content_size)))
		{
			free(result->next);
			return (NULL);
		}
		result = result->next;
		lst = lst->next;
	}
	return (head);
}
