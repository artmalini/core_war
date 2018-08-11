/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:49:59 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:50:04 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 144 == (T_DIR, T_REG)
** 208 == (T_IND, T_REG)
*/

void	vm_ld_dr(t_vm *vm, t_cmd *cmd, int one, int hex)
{
	if (vm->debug)
		ft_printf("|P\t%d| ld |%d| |r%d|\n", cmd->nbr_process, one, hex);
	cmd->reg[hex - 1] = one;
	if (one == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
	vm_next_step(vm, cmd, 7);
}

void	vm_ld_ir(t_vm *vm, t_cmd *cmd)
{
	short	two;
	int		two_val;
	int		pos;
	int		val;
	int		hex;

	two = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	two_val = two % IDX_MOD;
	val = (cmd->idx + two_val);
	pos = 0xFF & vm->arena[mdx(val)].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[mdx(val + 1)].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[mdx(val + 2)].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[mdx(val + 3)].acb;
	hex = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm_v_cmd(hex - 1, hex - 1, hex - 1))
	{
		if (vm->debug)
			ft_printf("|P\t%d| ld |%d| |r%d|\n", cmd->nbr_process, pos, hex);
		cmd->reg[hex - 1] = pos;
		cmd->carry = (pos == 0) ? 1 : 0;
	}
	vm_next_step(vm, cmd, 5);
}

void	vm_ld(t_vm *vm, t_cmd *cmd)
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
			vm_ld_dr(vm, cmd, one, hex);		
		else
			vm_next_step(vm, cmd, 7);
	}
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 208)
		vm_ld_ir(vm, cmd);
}
