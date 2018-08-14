/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_m_cmd_triger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:15:41 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:15:47 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_cmd_triger2(t_vm *vm, t_cmd *cmd, int hex)
{
	if (hex == 12)
		vm_fork(vm, &cmd);
	else if (hex == 13)
		vm_lld(vm, cmd, hex - 1);
	else if (hex == 14)
		vm_lldi(vm, cmd, hex - 1);
	else if (hex == 15)
		vm_lfork(vm, &cmd);
	else if (hex == 16)
		vm_aff(vm, cmd, hex - 1);
	else
		return ;
}

void	vm_cmd_triger(t_vm *vm, t_cmd *cmd, int hex)
{
	if (hex == 1)
		vm_live(vm, cmd);
	else if (hex == 2)
		vm_ld(vm, cmd, hex - 1);
	else if (hex == 3)
		vm_st(vm, cmd, hex - 1);
	else if (hex == 4)
		vm_add(vm, cmd, hex - 1);
	else if (hex == 5)
		vm_sub(vm, cmd, hex - 1);
	else if (hex == 6)
		vm_and(vm, cmd, hex - 1);
	else if (hex == 7)
		vm_or(vm, cmd, hex - 1);
	else if (hex == 8)
		vm_xor(vm, cmd, hex - 1);
	else if (hex == 9)
		vm_zjmp(vm, cmd);
	else if (hex == 10)
		vm_ldi(vm, cmd, hex - 1);
	else if (hex == 11)
		vm_sti(vm, cmd, hex - 1);
	else
		vm_cmd_triger2(vm, cmd, hex);
}
