/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:51:46 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:51:53 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 144 == (T_DIR, T_REG)
** 208 == (T_IND, T_REG)
*/

void	lld_ir_debug(int hex, int one)
{
	ft_printf("|P\t%d| lld |r%d| |%d|\n", hex, one);
}

void	vm_lld_dr(t_vm *vm, t_cmd *cmd, int one)
{
	cmd->reg[vm->arena[mdx(cmd->idx + 6)].acb - 1] = one;
	if (vm->debug)
	{
		ft_printf("|P\t%d| lld |r%d| |%d|\n",
			vm->arena[mdx(cmd->idx + 6)].acb, one);
	}
	if (one == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
	vm_next_step(vm, cmd, 7);
}

void	vm_lld_ir(t_vm *vm, t_cmd *cmd)
{
	short	two;
	int		pos;
	int		val;
	int		hex;

	two = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	val = mdx(cmd->idx + two);
	pos = 0xFF & vm->arena[val].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 1].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 2].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 3].acb;
	hex = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm_v_cmd(hex - 1, hex - 1, hex - 1))
	{
		cmd->reg[vm->arena[mdx(cmd->idx + 4)].acb - 1] = pos;
		cmd->carry = (pos == 0) ? 1 : 0;
		if (vm->debug)
			lld_ir_debug(hex, pos);
	}
	vm_next_step(vm, cmd,5);
}

void	vm_lld(t_vm *vm, t_cmd *cmd, int x)
{
	int		hex;
	int		one;

	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 144)
	{
		one = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
		hex = 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
		if (vm_v_cmd(hex - 1, hex - 1, hex - 1))
			vm_lld_dr(vm, cmd, one);
		else
			vm_next_step(vm, cmd, 7);
	}
	else if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 208)
		vm_lld_ir(vm, cmd);
	else
		vm_next_step(vm, cmd, vm_len_step(vm, cmd, x));
}
