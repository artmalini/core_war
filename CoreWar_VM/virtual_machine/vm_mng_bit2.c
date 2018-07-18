/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mng_bit2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:11:08 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:11:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_ddr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	int		tmp[5];

	tmp[3] = 6;
	tmp[4] = 4;
	if (let == 1)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) & vm_direct(vm, cmd, tmp);
	if (let == 2)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) | vm_direct(vm, cmd, tmp);
	if (let == 3)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) ^ vm_direct(vm, cmd, tmp);
	if (cmd->reg[arg[0] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_drr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_direct(vm, cmd, arg);
	if (let == 2)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_direct(vm, cmd, arg);
	if (let == 3)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_direct(vm, cmd, arg);
	if (cmd->reg[arg[1] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_rir(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_indir(vm, cmd, 3);
	if (let == 2)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_indir(vm, cmd, 3);
	if (let == 3)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_indir(vm, cmd, 3);
	if (cmd->reg[arg[1] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_irr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_indir(vm, cmd, 2);
	if (let == 2)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_indir(vm, cmd, 2);
	if (let == 3)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_indir(vm, cmd, 2);
	if (cmd->reg[arg[1] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}
