
#include "vm.h"

void	vm_load_ncurses(void)
{
	initscr();
	noecho();
	start_color();
	//init_color(COLOR_RED, 68, 0, 0);
	//init_pair(0, COLOR_WHITE, COLOR_BLACK);
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
	printw("\nLives for %.20s	%d Process: %d", vm->tab_champ[i].name, vm->tab_champ[i].prev_live, vm->tab_champ[i].nbr_process);
	printw(" Lives in current period: %d", vm->tab_champ[i].lives_in_period);
	printw("\t\t Total cycles: %d", vm->total_cycle);
}

void	vm_game_stat(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->nbr_next)
		vm_pl_stats(vm, i);
	attron(COLOR_PAIR(10));
	printw("\nCycle : %d Cycles to die: %d \n\n", vm->cycle, vm->cycle_to_die);
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
	vm_game_stat(vm);
	while (i < MEM_SIZE)
	{
		//printw(" ");
		//if (vm->arena[i].bold > 0)
		//	attron(A_BOLD);
		attron(COLOR_PAIR(vm->arena[i].rgb));
		printw("%02x", 0xFF & vm->arena[i].acb);
		attroff(COLOR_PAIR(vm->arena[i].rgb));
		printw(" ");
		// if (vm->arena[i].bold > 0)
		// {
		// 	attroff(A_BOLD);
		// 	vm->arena[i].bold -= 1;
		// }
		if ((i + 1) % 64 == 0)
		{ 
			//mem += 64;
			//if (i + 1 < MEM_SIZE)
			attron(COLOR_PAIR(k));
			print_logo(++j, vm);
				printw("\n");
		}		
		i++;		
	}
	printw("\n");
	refresh();
}
