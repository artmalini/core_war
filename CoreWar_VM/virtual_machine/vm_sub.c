/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:11:08 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:11:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_sub(t_vm *vm, t_cmd *cmd)
{
	int		a;
	int		b;
	int		c;

	a = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	b = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	c = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm_v_cmd(a - 1, b - 1, c - 1))
	{
		if (vm->debug)
			ft_printf("|P\t%d| sub |r%d| |r%d| |r%d|\n", cmd->nbr_process, a, b, c);
		cmd->reg[c - 1] = cmd->reg[a - 1] - cmd->reg[b - 1];
		cmd->carry = (cmd->reg[c - 1] == 0) ? 1 : 0;
		vm_next_step(vm, cmd, 5);
	}
	else
		vm_next_step(vm, cmd, 5);
}
