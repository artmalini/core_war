/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:55:00 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:55:05 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_zjmp(t_vm *vm, t_cmd *cmd)
{
	short	place;
	int		val;

	if (cmd->carry)
	{
		place = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
		place <<= 8;
		place += 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		val = (place % IDX_MOD);
		if (vm->debug)
			ft_printf("|P\t%d| zjmp |%d| OK\n", cmd->nbr_process, val);
		vm_next_step(vm, cmd, (val));
	}
	else
	{
		if (vm->debug)
			ft_printf("|P\t%d| zjmp FAILED\n", cmd->nbr_process);
		vm_next_step(vm, cmd, 3);
	}
}
