/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:48:36 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:48:45 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_add(t_vm *vm, t_cmd *cmd)
{
	int		a;
	int		b;
	int		c;

	a = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	b = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	c = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm_v_cmd(a - 1, b - 1, c - 1))
	{
		cmd->reg[c - 1] = cmd->reg[a - 1] + cmd->reg[b - 1];
		cmd->carry = (cmd->reg[c - 1] == 0) ? 1 : 0;
		if (vm->debug)
			ft_printf("|P\t%d| add |r%d| |r%d| |r%d|\n", cmd->nbr_process, a, b, c);
		vm_next_step(vm, cmd, 5);
	}
	else
		vm_next_step(vm, cmd, vm_new_step(vm, cmd, 0));
}
