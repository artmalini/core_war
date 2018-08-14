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

void	vm_aff(t_vm *vm, t_cmd *cmd, int x)
{
	int	arg1;
	int	cdg;

	cdg = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;	
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	if (cdg != 64 || (arg1 < 0 || arg1 > 16))
	{
		vm_next_step(vm, cmd, vm_len_step(vm, cmd, x));
		return ;
	}
	arg1 = cmd->reg[arg1 - 1];
	if (vm->visual)
		printw("%C\n", arg1 % 256);
	if (vm->aff)
		ft_printf("Aff: %c\n", (char)(arg1 % 256));
	vm_next_step(vm, cmd, vm_len_step(vm, cmd, x));
}
