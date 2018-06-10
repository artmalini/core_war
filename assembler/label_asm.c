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

int			find_link(char *str, t_core *file)
{
	t_cmd	*tmp;

	tmp = file->inst->cmd;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->arg1)
			{
				//ft_printf("STR %s\n", tmp->arg1 + 2);
				if (!ft_strcmp(str, tmp->arg1 + 2))
				{
					ft_printf("		@STR %s|%d|\n", str, tmp->byte_method_nbr);
					return (tmp->byte_method_nbr);
				}
			}
			if (tmp->arg2)
			{
				if (!ft_strcmp(str, tmp->arg2 + 2))
				{
					ft_printf("		@STR %s|%d|\n", str, tmp->byte_method_nbr);
					return (tmp->byte_method_nbr);
				}
			}
			if (tmp->arg3)
			{
				if (!ft_strcmp(str, tmp->arg3 + 2))
				{
					ft_printf("		@STR %s|%d|\n", str, tmp->byte_method_nbr);
					return (tmp->byte_method_nbr);
				}
			}
			tmp = tmp->next;
		}
		return (0);
	}
	return (0);
}

t_inst		*add_label(char *str, t_core *file)
{
	t_inst	*lst;
	int		i;

	i = 0;
	lst = NULL;
	lst = (t_inst *)malloc(sizeof(t_inst));
	if (lst)
	{
		lst->label = str ? ft_strdup(str) : NULL;
		lst->cmd = NULL;
		i = lst->cmd ? find_link(str, file) : 0;
		//lst->label_pos = file->count_pos;
		lst->label_pos = file->count_size - i;
		ft_printf("				label_pos|%d| |%d| |%d|\n", file->count_pos, file->count_size, i);
		//if (lst->cmd)
		//	ft_printf("				byte_method_nbr|%d|\n", lst->cmd->byte_method_nbr);
		file->count_pos = 0;
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