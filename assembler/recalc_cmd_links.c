/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalc_cmd_links.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:39:47 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:39:49 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			find_l(char *str, t_cmd *tmp, int label_pos)
{
	while (tmp)
	{
		if (tmp->arg1)
		{
			if (!ft_strcmp(str, tmp->arg1 + 2))// %:
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->arg1 + 1))// :
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		if (tmp->arg2)
		{
			if (!ft_strcmp(str, tmp->arg2 + 2))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->arg2 + 1))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		if (tmp->arg3)
		{
			if (!ft_strcmp(str, tmp->arg3 + 2))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->arg3 + 1))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		tmp = tmp->next;	
	}
}

void			recalc_cmd_links(t_core *file)
{
	t_inst	*tmp;

	tmp = file->inst;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->label)
				find_l(tmp->label, file->inst->cmd, tmp->label_pos);
			tmp = tmp->next;
		}
	}
}
