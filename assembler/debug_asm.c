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
		while (inst)
		{
			ft_printf("Line[22]: label_debug	|%s|\n", inst->label);
			inst = inst->next;
		}
}

void	cmd_debug(t_inst *inst)
{
	t_cmd	*comm;

	while (inst)
	{
		ft_printf("Line[33]: cmd_debug label	|%s|\n", inst->label);
		comm = inst->cmd;
		while (comm)
		{
			ft_printf("Line[37]: md_debug command	|%s| opcode|%d|\n", comm->command, comm->opcode);
			comm = comm->next;
		}
		inst = inst->next;
	}
}