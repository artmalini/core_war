/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 22:57:56 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 22:57:58 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	label_debug(t_core *file)
{
		t_inst	*inst;

		inst = file->inst;
		ft_printf("File Count Size:	[%d] file->name|%s|\n", file->count_size, file->name);
		while (inst)
		{
			ft_printf("Label (Name/Positions):	[%s]/[%d]\n", inst->label, inst->label_pos);
			inst = inst->next;
		}
}

void	cmd_debug(t_inst *inst)
{
	t_cmd	*comm;

	while (inst)
	{
		ft_printf("Label (Name/Positions): [%s]/[%d]\n", inst->label, inst->label_pos);
		comm = inst->cmd;
		while (comm)
		{
			ft_printf("CMD:	[%s]\nOpcode:	[%d]\nSize:	[%d]\nByte_nbr(for command): [%d]\n\n", comm->command, comm->opcode, comm->cmd_size, comm->byte_nbr);
			comm = comm->next;
		}
		inst = inst->next;
	}
}