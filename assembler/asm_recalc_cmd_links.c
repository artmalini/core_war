/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_recalc_cmd_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:39:47 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:39:49 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		find_l(t_cmd *tmp, char *str, int label_pos)
{
	while (tmp)
	{
		if (tmp->args[FIRST])
		{
			if (!ft_strcmp(str, tmp->args[FIRST] + 2))
				tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->args[FIRST] + 1))
				tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		if (tmp->args[SECOND])
		{
			if (!ft_strcmp(str, tmp->args[SECOND] + 2))
				tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->args[SECOND] + 1))
				tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		if (tmp->args[THIRD])
		{
			if (!ft_strcmp(str, tmp->args[THIRD] + 2))
				tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->args[THIRD] + 1))
				tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		tmp = tmp->next;
	}
}

void		recalc_cmd_links(t_core *file)
{
	t_inst	*tmp;

	tmp = file->inst;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->label)
				find_l(file->inst->cmd, tmp->label, tmp->label_pos);
			tmp = tmp->next;
		}
	}
}
