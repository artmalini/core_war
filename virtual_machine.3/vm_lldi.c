/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:52:05 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:52:10 by amakhiny         ###   ########.fr       */
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

void	vm_lldi_write(t_vm *vm, t_cmd *cmd, int val, int i)
{
	int		one;
	int		val1;
	char	a;

	val1 = cmd->idx - val + i;
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
		cmd->reg[vm->arena[mdx(cmd->idx)].acb - 1] = one;
		if (vm->debug)
			ft_printf("|P\t%d| lldi |r%d| |%d|\n", a, one);
	}
}

void	lldi_idr_ddr(t_vm *vm, t_cmd *cmd, int hex)
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
		vm_lldi_write(vm, cmd, 6, (res % IDX_MOD));
	}
	if (hex == 164)
	{
		arg[3] = 2;
		arg[4] = 2;
		tmp[3] = 4;
		tmp[4] = 2;
		res = vm_direct(vm, cmd, arg) + vm_direct(vm, cmd, tmp);
		vm_next_step(vm, cmd, 6);
		vm_lldi_write(vm, cmd, 6, res);
	}
}

void	lldi_irr_drr(t_vm *vm, t_cmd *cmd, int hex)
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
			res = vm_direct(vm, cmd, arg) + a;
		vm_next_step(vm, cmd, 5);
		vm_lldi_write(vm, cmd, 5, res);
	}
	if (hex == 212)
	{
		a = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		if (vm_v_cmd(a - 1, a - 1, a - 1))
			res = vm_indir(vm, cmd, 2) + a;
		vm_next_step(vm, cmd, 5);
		vm_lldi_write(vm, cmd, 5, (res % IDX_MOD));
	}
}

void	vm_lldi_rdr(t_vm *vm, t_cmd *cmd, int hex)
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
			res = a + vm_direct(vm, cmd, arg);
		vm_next_step(vm, cmd, 5);
		vm_lldi_write(vm, cmd, 5, res);
	}
}

void	vm_lldi(t_vm *vm, t_cmd *cmd)
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
			res = (a - 1) + (b - 1);
			vm_next_step(vm, cmd, 4);
			vm_lldi_write(vm, cmd, 4, res);
		}
	}
	if (hex == 228 || hex == 164)
		lldi_idr_ddr(vm, cmd, hex);
	if (hex == 212 || hex == 148 || hex == 100)
	{
		lldi_irr_drr(vm, cmd, hex);
		vm_lldi_rdr(vm, cmd, hex);
	}
	vm_next_step(vm, cmd, 1);
}
