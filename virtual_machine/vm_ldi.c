/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:50:35 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:50:41 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 84  == (T_REG, T_REG, T_REG)
** 100 == (T_REG, T_DIR, T_REG)
** 148 == (T_DIR, T_REG, T_REG)
** 212 == (T_IND, T_REG, T_REG)
** 228 == (T_IND, T_DIR, T_REG)
** 164 == (T_DIR, T_DIR, T_REG)
*/
//		ft_printf("|P\t%d| sti |%d| |r%d|\n\t\t (with pc and mod %d)\n", cmd->nbr_process, direct, reg1, cmd->idx + direct);
void	vm_ldi_write(t_vm *vm, t_cmd *cmd, int val, int i)
{
	int		one;
	int		val1;
	char	a;

	val1 = (cmd->idx - val) + i;
	one = 0xFF & vm->arena[mdx(val1)].acb;
	one <<= 8;
	one += 0xFF & vm->arena[mdx(val1 + 1)].acb;
	one <<= 8;
	one += 0xFF & vm->arena[mdx(val1 + 2)].acb;
	one <<= 8;
	one += 0xFF & vm->arena[mdx(val1 + 3)].acb;
	a = 0xFF & vm->arena[mdx(cmd->idx)].acb;
	if (vm_v_cmd(a - 1, a - 1, a - 1))
	{
		cmd->reg[a - 1] = one;
		if (vm->debug)
			ft_printf("|P\t%d| ldi |%d| |r%d|\n\t\t (with pc and mod %d)\n", cmd->nbr_process, i, a, val1);
	}
	vm_next_step(vm, cmd, 1);
}

void	vm_idr_ddr(t_vm *vm, t_cmd *cmd, int hex)
{
	int		res;
	int		arg[5];
	int		tmp[5];

	if (hex == 228)
	{
		arg[3] = 4;
		arg[4] = 2;
		res = vm_indir(vm, cmd, 2) + vm_direct(vm, cmd, arg);
		vm_next_step(vm, cmd, 6);
		vm_ldi_write(vm, cmd, 6, (res % IDX_MOD));
	}
	if (hex == 164)
	{
		arg[3] = 2;
		arg[4] = 2;
		tmp[3] = 4;
		tmp[4] = 2;
		res = vm_direct(vm, cmd, arg) + vm_direct(vm, cmd, tmp);
		vm_next_step(vm, cmd, 6);
		vm_ldi_write(vm, cmd, 6, (res % IDX_MOD));
	}
}

void	vm_irr_drr(t_vm *vm, t_cmd *cmd, int hex)
{
	char	a;
	int		res;
	int		arg[5];

	a = 0;
	res = 0;
	if (hex == 148)
	{
		arg[3] = 2;
		arg[4] = 2;
		a = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		if (vm_v_cmd(a - 1, a - 1, a - 1))
			res = vm_direct(vm, cmd, arg) + cmd->reg[a - 1];
		vm_next_step(vm, cmd, 5);
		vm_ldi_write(vm, cmd, 5, (res % IDX_MOD));
	}
	if (hex == 212)
	{
		a = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		if (vm_v_cmd(a - 1, a - 1, a - 1))
			res = vm_indir(vm, cmd, 2) + cmd->reg[a - 1];
		vm_next_step(vm, cmd, 5);
		vm_ldi_write(vm, cmd, 5, (res % IDX_MOD));
	}
}

void	vm_ldi_rdr(t_vm *vm, t_cmd *cmd, int hex)
{
	char	a;
	int		res;
	int		arg[5];

	a = 0;
	res = 0;
	if (hex == 100)
	{
		arg[3] = 3;
		arg[4] = 2;
		a = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		if (vm_v_cmd(a - 1, a - 1, a - 1))
			res = cmd->reg[a - 1] + vm_direct(vm, cmd, arg);
		vm_next_step(vm, cmd, 5);
		vm_ldi_write(vm, cmd, 5, (res % IDX_MOD));
	}
}

void	vm_ldi(t_vm *vm, t_cmd *cmd, int x)
{
	char	a;
	char	b;
	int		res;
	int		hex;

	hex = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
	if (hex == 84)
	{
		a = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		b = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
		if (vm_v_cmd(a - 1, a - 1, b - 1))
		{
			res = cmd->reg[a - 1] + cmd->reg[b - 1];
			vm_next_step(vm, cmd, 4);
			vm_ldi_write(vm, cmd, 4, (res % IDX_MOD));
		}
		else
			vm_next_step(vm, cmd, 4);
	}
	else if (hex == 228 || hex == 164)
		vm_idr_ddr(vm, cmd, hex);
	else if (hex == 212 || hex == 148 || hex == 100)
	{
		vm_irr_drr(vm, cmd, hex);
		vm_ldi_rdr(vm, cmd, hex);
	}
	else
		vm_next_step(vm, cmd, vm_len_step(vm, cmd, x));
}
