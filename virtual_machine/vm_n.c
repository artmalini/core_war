/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_n.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:18:03 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:18:06 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_load_ncurses(void)
{
	initscr();
	noecho();
	start_color();
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

void	vm_pl_stats(t_vm *vm, int i)
{
	attron(COLOR_PAIR(vm->tab_champ[i].rgb));
	printw(" Lives for %.18s \t\t%d \t\tProcess: %d", vm->tab_champ[i].name,
		vm->tab_champ[i].prev_live, vm->tab_champ[i].nbr_process);
	printw("\t\tLives in current period: %d\n", vm->tab_champ[i].lives_in_period);
}

void	vm_win_recalc(t_vm *vm)
{
	int		win;

	win = 0;
	if (vm->total_cycle > 1)
	{
		win = vm_vis_winner(vm);
		if (vm->total_cycle - vm->tab_champ[win].prev_live == 1)
			vm->total_cycle--;
	}
}

void	vm_game_stat(t_vm *vm, int j)
{
	int		i;

	i = -1;
	while (++i < vm->nbr_next)
		vm_pl_stats(vm, i);
	attron(COLOR_PAIR(10));
	printw(" Cycle: %d\t\t\tCycles to die:\t%d\n", vm->cycle, vm->cycle_to_die);		
	if (vm->win)
		vm_win_recalc(vm);	
	printw(" Total cycles:\t\t\t%d\t\t\t['Z' key for pause game] ['SPACE' for slow/fast game]\n", vm->total_cycle);	
	if (vm->cycle_to_die == 0 && vm->total_cycle != 0 && j != 0)
	{		
		attron(COLOR_PAIR(vm->tab_champ[vm_vis_winner(vm)].rgb));
		printw("\t\t\t\t\t\t Congratulations: %.20s!!! \tPress any key to exit.",
			vm->tab_champ[vm_vis_winner(vm)].name);
		attroff(COLOR_PAIR(vm->tab_champ[vm_vis_winner(vm)].rgb));
	}
}


void	vm_vis_arena(t_vm *vm)
{
	int	i;
	int	j;
	int	k;

	erase();
	i = 0;
	j = -1;
	k = 0;
	if (vm->cycle < 400)
		k = 1;
	else if (vm->cycle > 400 && vm->cycle < 800)
		k = 2;
	else if (vm->cycle > 800 && vm->cycle < 1200)
		k = 3;
	else
		k = 4;
	//vm_game_stat(vm, j);
	//printw("\n\n ");
	while (i < MEM_SIZE)
	{
		//printw(" ");
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
		if ((i + 1) % 64 == 0)
		{ 
			//mem += 64;
			//if (i + 1 < MEM_SIZE)
			attron(COLOR_PAIR(k));
			print_logo(++j, vm);
				printw("\n ");
		}		
		i++;		
	}
	printw("\n");
	refresh();
}
