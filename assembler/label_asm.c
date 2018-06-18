/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:08:27 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:08:28 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_inst		*add_label(char *str, t_core *file)
{
	t_inst	*lst;

	lst = NULL;
	lst = (t_inst *)malloc(sizeof(t_inst));
	if (lst)
	{
		lst->label = str ? ft_strdup(str) : NULL;
		lst->cmd = NULL;
		lst->label_pos = file->count_size;
		lst->next = NULL;
	}
	return (lst);
}

void		push_laybel(char *str, t_inst **lst, t_core *file)
{
	t_inst	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add_label(str, file);
	}
	else
	{
		*lst = add_label(str, file);
	}
}