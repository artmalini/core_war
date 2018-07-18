/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mng_bit1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:11:08 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:11:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_rdr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
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

void	vm_rrr_bit(t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] & cmd->reg[arg[1] - 1];
	if (let == 2)
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] | cmd->reg[arg[1] - 1];
	if (let == 3)
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] ^ cmd->reg[arg[1] - 1];
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_idr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) & vm_direct(vm, cmd, arg);
	if (let == 2)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) | vm_direct(vm, cmd, arg);
	if (let == 3)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) ^ vm_direct(vm, cmd, arg);
	if (cmd->reg[arg[0] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_iir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) & vm_indir(vm, cmd, 4);
	if (let == 2)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) | vm_indir(vm, cmd, 4);
	if (let == 3)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) ^ vm_indir(vm, cmd, 4);
	if (cmd->reg[arg[0] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_dir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) & vm_indir(vm, cmd, 6);
	if (let == 2)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) | vm_indir(vm, cmd, 6);
	if (let == 3)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) ^ vm_indir(vm, cmd, 6);
	if (cmd->reg[arg[0] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}
