/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:41:21 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/18 16:41:22 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	load_champ_to(t_vm *vm, t_champ champ, int memory_index)
{
	int	index;

	index = 0;
	while (index < champ.weight && (index + memory_index) < MEM_SIZE)
	{
		vm->arena[index + memory_index] = (unsigned char)champ.prog[index];
		index++;
	}
}

void		vm_load_champs(t_vm *vm)
{
	int	space_bt_champs;
	int	num_players;
	int	space;

	num_players = 0;
	space_bt_champs = MEM_SIZE / vm->nbr_next;
	if (vm->nbr_next == 1)
		space_bt_champs = 0;
	space = 0;
	while (num_players < vm->nbr_next)
	{
		load_champ_to(vm, vm->tab_champ[num_players], space);
		space += space_bt_champs;
		num_players++;
	}
}
