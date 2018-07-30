/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:55:24 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 13:55:28 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		cmd_lst_free(t_cmd *c)
{
	t_cmd	*tmp;

	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}
}

void		cmd_free(t_cmd *c)
{
	while (c)
	{
		ft_strdel(&c->command);
		ft_strdel(&c->str);
		ft_strdel(&c->args[FIRST]);
		ft_strdel(&c->args[SECOND]);
		ft_strdel(&c->args[THIRD]);
		c = c->next;
	}
}

void		inst_data_free(t_inst *inst)
{
	while (inst)
	{
		ft_strdel(&inst->label);
		inst = inst->next;
	}
}

void		inst_free(t_inst *first)
{
	t_inst	*tmp;

	while (first)
	{
		tmp = first;
		first = first->next;
		free(tmp);
	}
}

void		free_struct_tcore(t_core *file)
{
	if (file)
	{
		if (file->name)
			ft_strdel(&file->name);
		if (file->comment)
			ft_strdel(&file->comment);
		if (file->filename)
			ft_strdel(&file->filename);
		if (file->inst)
		{
			if (file->inst->cmd)
			{
				cmd_free(file->inst->cmd);
				cmd_lst_free(file->inst->cmd);
			}
			inst_data_free(file->inst);
			inst_free(file->inst);
		}
	}
}
