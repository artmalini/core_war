/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:11:08 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:11:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	vm_getpl(t_vm *vm, int place)
{
	int		 i;

	i = -1;
	while (++i < vm->nbr_next)
	{
		if (vm->tab_champ[i].id == place)
			return (i);
	}
	return (-1);
}

void		vm_live(t_vm *vm, t_cmd *cmd)
{
	int		place;
	int		id;

	place = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
	place <<= 8;
	place += 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	place <<= 8;
	place += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	place <<= 8;
	place += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	//place = place > 0 ? place * -1 : place;
	//id = vm_getpl(vm);
	id = vm_getpl(vm, place);
	if (vm->debug)
		ft_printf("|P\t%d| live id %d place|%d|\n", cmd->nbr_process, id, place);
	//id = vm->tab_champ[place];
	//id = 0;
	if (id > -1)
	{
		vm->lifes += 1;
		vm->win = id;
		vm->tab_champ[id].prev_live = vm->total_cycle;
		vm->tab_champ[id].lives_in_period += 1;
		cmd->life = 1;
		vm_next_step(vm, cmd, 5);
	}
	else
		vm_next_step(vm, cmd, 5);
}
