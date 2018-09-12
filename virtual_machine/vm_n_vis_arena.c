/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_n_vis_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:06:40 by amakhiny          #+#    #+#             */
/*   Updated: 2018/08/23 12:06:47 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			vm_k_cycle(t_vm *vm)
{
	int		k;

	k = 0;
	if (vm->cycle < 400)
		k = 1;
	else if (vm->cycle > 400 && vm->cycle < 800)
		k = 2;
	else if (vm->cycle > 800 && vm->cycle < 1200)
		k = 3;
	else
		k = 4;
	return (k);
}

void		vm_style_arena(t_vm *vm, int i)
{
	if (vm->arena[i].bold > 0)
		attron(A_BOLD);
	attron(COLOR_PAIR(vm->arena[i].rgb));
	printw("%02x", 0xFF & vm->arena[i].acb);
	attroff(COLOR_PAIR(vm->arena[i].rgb));
	printw(" ");
	if (vm->arena[i].bold > 0)
	{
		attroff(A_BOLD);
		vm->arena[i].bold -= 1;
	}
}

void		vm_vis_arena(t_vm *vm)
{
	int	i;
	int	j;
	int	k;

	erase();
	i = 0;
	j = -1;
	k = vm_k_cycle(vm);
	//vm_game_stat(vm, j);
	printw("\n ");
	while (i < MEM_SIZE)
	{
		vm_style_arena(vm, i);
		if ((i + 1) % 64 == 0)
		{
			attron(COLOR_PAIR(k));
			print_logo(++j, vm);
			printw("\n ");
		}
		i++;
	}
	printw("\n");
	refresh();
}
