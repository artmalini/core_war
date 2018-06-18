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
		ft_printf("File Count Size:	[%d]\n file->name|%s|\n file->comment|%s|\n", file->count_size, file->name, file->comment);
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
			ft_printf("CMD:	[%s]\nOpcode:	[%d]\nCount bytes:	[%d]\n\n", comm->command, comm->opcode, comm->cmd_size);
			comm = comm->next;
		}
		inst = inst->next;
	}
}

void		print_new_args(t_core *file, t_cmd	*lst, char **args, int nbr_args)
{
	int 	i;

	i = 0;
	ft_printf("\n#### GOOD 0%d-ARGUMENTS "
                      "(in Array: mac[%d])\n", nbr_args, nbr_args - 1);
	if (file->st[DEBUG_ON] && file->st[DEBUG_ARG] == ON)
	{
		while (i < nbr_args)
		{
			ft_printf("#### 0%d-ARGUMENT - [%s]\n", (i + 1), args[i]);
			i++;
		}
	}
	ft_printf("#### INSERT STR  - [%s]\n", lst->str);                           //Print String with arguments for Cod-Age
    ft_printf("\n");
}
