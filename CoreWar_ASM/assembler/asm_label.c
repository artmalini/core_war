/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:08:27 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:08:28 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_inst		*add_label(t_core *file, t_inst	*lst, char *str)
{

	if (!(lst = ft_memalloc(sizeof(t_inst))))
		ft_error(file, ERROR_MEMORY);
	if (lst)
	{
		lst->label = str ? ft_strdup(str) : NULL;
		file->error->current_label = lst->label;
		lst->cmd = NULL;
		lst->label_pos = file->count_size;
		lst->next = NULL;

	}
	return (lst);
}

void		push_laybel(t_core *file, t_inst **lst, char *str)
{
	t_inst	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add_label(file, NULL, str);
	}
	else
		*lst = add_label(file, NULL, str);
}