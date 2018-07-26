/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_free_and_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 01:39:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/18 01:39:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		free_vm(t_vm *vm)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;
	int		i;

	i = -1;
	while (++i < vm->nbr_next)
	{
		free(vm->tab_champ[i].name);
		free(vm->tab_champ[i].prog);
	}
	if (vm->cmd)
	{
		tmp = vm->cmd;
		while (tmp)
		{
			tmp1 = tmp;
			tmp = tmp->next;
			free(tmp1);
		}
	}
	free(vm);
}

void		init(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
//		vm->tab_champ[i].weight = 0;
		vm->tab_champ[i].file_weight = OFF;
		vm->tab_champ[i].bot_weight = OFF;
		vm->tab_champ[i].rgb = 1 + (i % 4);
		vm->tab_champ[i].id = OFF;
		vm->tab_champ[i].nbr_process = ON;
		vm->tab_champ[i].alive = OFF;
		vm->tab_champ[i].old_check = OFF;
		vm->tab_champ[i].prev_live = OFF;
		vm->tab_champ[i].lives_in_period = OFF;
		i++;
	}
	vm->win = -1;
	vm->fd = OFF;
	vm->cmd = NULL;
	vm->cycle = OFF;
	vm->lifes = OFF;
	vm->nbr_next = OFF;
	vm->dump_cycle = -1;
	vm->last_check = OFF;
	vm->total_cycle = OFF;
	vm->total_process = ON;
	vm->current_player = OFF;
	vm->total_lives_period = OFF;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_before_checking = CYCLE_TO_DIE;
}
