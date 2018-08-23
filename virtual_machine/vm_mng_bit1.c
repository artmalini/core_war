/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mng_bit1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:52:47 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:52:52 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_rdr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
	{
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_ffdir(vm, cmd, arg);
		if (vm->debug)
			ft_printf("|P\t%d| and |r%d|\n", cmd->nbr_process, arg[1]);
	}
	if (let == 2)
	{
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_ffdir(vm, cmd, arg);
		if (vm->debug)
			ft_printf("|P\t%d| or |r%d|\n", cmd->nbr_process, arg[1]);
	}
	if (let == 3)
	{
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_ffdir(vm, cmd, arg);
		if (vm->debug)
			ft_printf("|P\t%d| xor |r%d|\n", cmd->nbr_process, arg[1]);
	}
	if (cmd->reg[arg[1] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_rrr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
	{
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] & cmd->reg[arg[1] - 1];
		if (vm->debug)
			ft_printf("|P\t%d| and |r%d|\n", cmd->nbr_process, arg[2]);
	}
	if (let == 2)
	{
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] | cmd->reg[arg[1] - 1];
		if (vm->debug)
			ft_printf("|P\t%d| or |r%d|\n", cmd->nbr_process, arg[2]);
	}
	if (let == 3)
	{
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] ^ cmd->reg[arg[1] - 1];
		if (vm->debug)
			ft_printf("|P\t%d| xor |r%d|\n", cmd->nbr_process, arg[2]);
	}
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_idr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
	{
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) & vm_ffdir(vm, cmd, arg);
		if (vm->debug)
			ft_printf("|P\t%d| and |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (let == 2)
	{
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) | vm_ffdir(vm, cmd, arg);
		if (vm->debug)
			ft_printf("|P\t%d| or |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (let == 3)
	{
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) ^ vm_ffdir(vm, cmd, arg);
		if (vm->debug)
			ft_printf("|P\t%d| xor |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (cmd->reg[arg[0] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_iir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
	{
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) & vm_indir(vm, cmd, 4);
		if (vm->debug)
			ft_printf("|P\t%d| and |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (let == 2)
	{
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) | vm_indir(vm, cmd, 4);
		if (vm->debug)
			ft_printf("|P\t%d| or |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (let == 3)
	{
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) ^ vm_indir(vm, cmd, 4);
		if (vm->debug)
			ft_printf("|P\t%d| xor |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (cmd->reg[arg[0] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_dir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
	{
		cmd->reg[arg[0] - 1] = vm_ffdir(vm, cmd, arg) & vm_indir(vm, cmd, 6);
		if (vm->debug)
			ft_printf("|P\t%d| and |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (let == 2)
	{
		cmd->reg[arg[0] - 1] = vm_ffdir(vm, cmd, arg) | vm_indir(vm, cmd, 6);
		if (vm->debug)
			ft_printf("|P\t%d| or |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (let == 3)
	{
		cmd->reg[arg[0] - 1] = vm_ffdir(vm, cmd, arg) ^ vm_indir(vm, cmd, 6);
		if (vm->debug)
			ft_printf("|P\t%d| xor |r%d|\n", cmd->nbr_process, arg[0]);
	}
	if (cmd->reg[arg[0] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}
