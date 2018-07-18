/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 01:37:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/18 01:37:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_pl_stats(t_vm *vm, int i)
{
	attron(COLOR_PAIR(vm->tab_champ[i].rgb));
	printw("\nLives for %.20s	%d Process: %d",
		   vm->tab_champ[i].name, vm->tab_champ[i].prev_live,
		   vm->tab_champ[i].nbr_process);
	printw(" Lives in current period: %d",
		   vm->tab_champ[i].lives_in_period);
}

void		vm_game_stat(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->nbr_next)
		vm_pl_stats(vm, i);
	attron(COLOR_PAIR(10));
	printw("\nCycle : %d Cycles to die: %d \n\n", vm->cycle, vm->cycle_to_die);
}

void		vm_load_ncurses(void)
{
	initscr();
	noecho();
	start_color();
	//init_color(COLOR_RED, 68, 0, 0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_pair(5, COLOR_WHITE, COLOR_RED);
	init_pair(6, COLOR_WHITE, COLOR_YELLOW);
	init_pair(7, COLOR_WHITE, COLOR_GREEN);
	init_pair(8, COLOR_WHITE, COLOR_CYAN);

	init_pair(9, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(11, COLOR_WHITE, COLOR_BLACK);
	curs_set(FALSE);
}