/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_m_init1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:03:31 by amakhiny          #+#    #+#             */
/*   Updated: 2018/08/23 12:03:37 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_create_arena(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i].acb = 0;
		vm->arena[i].rgb = 11;
		vm->arena[i].asc_rgb = 11;
		vm->arena[i].flag = 0;
		vm->arena[i].overlap = 0;
		vm->arena[i].pl = 0;
		vm->arena[i].bold = 0;
		i++;
	}
}

void	vm_init_pl(t_vm *vm)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->tab_champ[i].weight = 0;
		vm->tab_champ[i].rgb = 1 + (i % 4);
		vm->tab_champ[i].id = -1;
		vm->tab_champ[i].nbr_process = 1;
		vm->tab_champ[i].prev_live = 0;
		vm->tab_champ[i].lives_in_period = 0;
	}
}

void	vm_init(t_vm *vm)
{
	vm_init_pl(vm);
	vm->fd = 0;
	vm->dump_cycle = -1;
	vm->visual = 0;
	vm->nbr_next = 0;
	vm->last_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->lifes = 0;
	vm->win = 0;
	vm->total_process = 0;
	vm->aff = 0;
	vm->cycle = 0;
	vm->total_cycle = 0;
	vm->debug = 0;
	vm->show_live = 0;
	vm->on = 0;
	vm->mus = 0;
	vm->cmd = NULL;
}
