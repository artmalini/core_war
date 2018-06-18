/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_asm_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:55:24 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 13:55:28 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	cmd_free(t_cmd *cmd)
{
	while (cmd)
	{
		ft_strdel(&cmd->command);
		ft_strdel(&cmd->str);
		ft_strdel(&cmd->arg1);
		ft_strdel(&cmd->arg2);
		ft_strdel(&cmd->arg3);
		cmd = cmd->next;
	}
}

void	cmd_lst_free(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	inst_data_free(t_inst *inst)
{
	while (inst)
	{
		ft_strdel(&inst->label);
		inst = inst->next;
	}
}

void	inst_free(t_inst *first)
{
	t_inst	*tmp;

	tmp = first;
	while (first)
	{
		tmp = first;
		first = first->next;
		free(tmp);
	}
}

void	free_struct_tcore(t_core *file)
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
