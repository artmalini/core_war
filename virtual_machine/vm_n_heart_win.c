/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_n_heart_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:18:32 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:18:38 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vm_vis_winner(t_vm *vm)
{
	int			i;
	int			j;

	i = -1;
	j = 0;	
	while (++i < vm->nbr_next)
	{
		if (vm->tab_champ[i].prev_live >
			vm->tab_champ[j].prev_live)
		{
			j = i;
		}
	}
	return (j);
}

void	draw_winner(int j, t_vm *vm)
{
	int		pl;

	pl = vm_vis_winner(vm);
	attron(COLOR_PAIR(1));
	vm_n_draw_win(j, pl);	
}

void	draw_pl_heart(int j, t_vm *vm)
{
	attron(COLOR_PAIR(1));
	if (vm->cycle_to_die > 0)
	{
		if (j == 21 || j == 27 || j == 33 || j == 39)
			printw("\t ###    ###");
		if (j == 22 || j == 28 || j == 34 || j == 40)
			printw("\t#####  #####");
		if (j == 23 || j == 29 || j == 35 || j == 41)
			printw("\t ##########");
		if (j == 24 || j == 30 || j == 36 || j == 42)
			printw("\t   ######");
		if (j == 25 || j == 31 || j == 37 || j == 43)
			printw("\t     ##");
	}
	if (vm->cycle_to_die == 0 && vm->total_cycle != 0)
		draw_winner(j, vm);
}
