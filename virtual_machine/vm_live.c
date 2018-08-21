/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:51:28 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:51:35 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vm_getpl(t_vm *vm, int place)
{
	int i;

	i = -1;
	while (++i < vm->nbr_next)
	{
		if (vm->tab_champ[i].id == place)
			return (i);
	}
	return (-1);
}

void	vm_live(t_vm *vm, t_cmd *cmd)
{
	int	place;
	int	id;

	place = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
	place <<= 8;
	place += 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	place <<= 8;
	place += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	place <<= 8;
	place += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	id = vm_getpl(vm, place * -1);
	if (vm->debug)
		ft_printf("|P\t%d| live |%d|\n",  cmd->nbr_process, place);

	cmd->life = 1;
	cmd->on = 1;
	vm->lifes += 1;
	if (id > -1)
	{
		vm->tab_champ[id].prev_live = vm->total_cycle;
		vm->tab_champ[id].lives_in_period += 1;
		if (vm->show_live)
			ft_printf("A process shows that player %d (%s) is alive\n",
				vm->tab_champ[id].id, vm->tab_champ[id].name);
		vm_next_step(vm, cmd, 5);
	}
	else
		vm_next_step(vm, cmd, 5);
}
