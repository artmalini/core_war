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

static void	load_champ_to(t_vm *vm, t_champ champ, int memory_index, int num_pl)
{
	int	index;

	index = 0;
	while (index < champ.weight && (index + memory_index) < MEM_SIZE)
	{
		vm->arena[index + memory_index].acb = 0xFF & champ.prog[index];
		vm->arena[index + memory_index].rgb = 1 + num_pl % 4;
		vm->arena[index + memory_index].asc_rgb = 1 + num_pl % 4;
		//if (index == 0)
		//	vm->arena[index + memory_index].hit = 1;
		//vm->arena[index + memory_index].o_acb = 0xFF & champ.prog[index];
		index++;
	}
}

void		vm_check_n_uniq(t_vm *vm)
{
	int		i;
	int		nbr;

	i = -1;
	nbr = -1;
	while (++i < vm->nbr_next)
	{
		if (vm->tab_champ[i].id == nbr)
		{
			ft_printf("Error: You need write different player number after -n argument\n");
			free_vm(vm);
			exit(1);
		}
		nbr = vm->tab_champ[i].id;		
	}
}

void		vm_load_champs(t_vm *vm)
{
	int		space_bt_champs;
	int		i;
	int		space;
	int		nbr;

	i = -1;
	space_bt_champs = MEM_SIZE / vm->nbr_next;
	if (vm->nbr_next == 1)
		space_bt_champs = 0;
	space = 0;
	nbr = vm->nbr_next - 1;
	vm_check_n_uniq(vm);
	ft_printf("Introducing contestants...\n");
	while (++i < vm->nbr_next)
	{
		
		vm->tab_champ[i].idx = space;
		vm->tab_champ[i].ready = nbr;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			vm->tab_champ[i].id, vm->tab_champ[i].weight,
			vm->tab_champ[i].name, vm->tab_champ[i].comment);				
		load_champ_to(vm, vm->tab_champ[i], space, i);
		space += space_bt_champs;
		nbr--;
	}
}
