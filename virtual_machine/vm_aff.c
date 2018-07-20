/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 11:42:45 by tvertohr          #+#    #+#             */
/*   Updated: 2018/07/15 11:42:47 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// int	is_reg(int value)
// {
// 	if (value > 0 && value < REG_NUMBER)
// 		return (1);
// 	return (0);
// }

// int	get_reg(t_vm *vm, int *i)
// {
// 	int	reg;

// 	reg = 0;
// 	reg = (unsigned char)vm->arena[(*i) % MEM_SIZE].acb;
// 	(*i)++;
// 	return (reg);
// }

void	vm_aff(t_vm *vm, t_cmd *cmd)
{
	int	arg1;
	int	pc;

	//cmd->idx++;
	//pc = cmd->idx + 1;
	pc = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
	if (!(vm_v_cmd(pc - 1, pc - 1, arg1 - 1)))
	{
		vm_next_step(vm, cmd, 3);
		return ;
	}
	arg1 = cmd->reg[arg1 - 1];
	//if not visual
	ft_printf("Aff : %C\n", arg1 % 256);
	if (arg1 % 256 == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
	vm_next_step(vm, cmd, 3);
}
