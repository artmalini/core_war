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

void	vm_aff(t_vm *vm, t_cmd *cmd)
{
	int	arg1;
	int	cdg;

	cdg = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;	
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	if (cdg != 64 || (arg1 < 0 || arg1 > 16))
	{
		vm_next_step(vm, cmd, 3);
		return ;
	}
	arg1 = cmd->reg[arg1 - 1];
	//if not visual
	if (vm->debug)
		ft_printf("Aff : %C\n", arg1 % 256);
	else
		printw("%C\n", arg1 % 256);
	vm_next_step(vm, cmd, 3);
}
