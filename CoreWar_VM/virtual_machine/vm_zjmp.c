/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:11:08 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:11:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				vm_zjmp(t_vm *vm, t_cmd *cmd)
{
	unsigned short	place;

	if (cmd->carry)
	{
		place = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
		place <<= 8;
		place += 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		vm_next_step(vm, cmd, ((short)place % IDX_MOD));
	}
	else
		vm_next_step(vm, cmd, 3);
}
