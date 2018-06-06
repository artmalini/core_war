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
		ft_printf("Line[20] file count size |%d|\n", file->count_size);
		while (inst)
		{
			ft_printf("Line[22]: label_debug	|%s|	label_pos|%d|\n", inst->label, inst->label_pos);
			inst = inst->next;
		}
}

void	cmd_debug(t_inst *inst)
{
	t_cmd	*comm;

	while (inst)
	{
		ft_printf("Line[33]: cmd_debug label	|%s| label_pos|%d|\n", inst->label, inst->label_pos);
		comm = inst->cmd;
		while (comm)
		{
			ft_printf("Line[37]: md_debug command	|%s|	opcode|%d|	cmd_size|%d|\n", comm->command, comm->opcode, comm->cmd_size);
			comm = comm->next;
		}
		inst = inst->next;
	}	
}