
#include "vm.h"

void	print_logo4(int j, t_vm *vm)
{
	if (j >= 32 && j <= 37 && vm->nbr_next >= 3)
	{
		if (j == 32)
		{
			attron(COLOR_PAIR(vm->tab_champ[2].rgb));
			printw("%.16s", vm->tab_champ[2].name);
		}
		draw_pl_heart(j, vm);
	}
	if (j >= 38 && j <= 43 && vm->nbr_next == 4)
	{
		if (j == 38)
		{
			attron(COLOR_PAIR(vm->tab_champ[3].rgb));
			printw("%.16s", vm->tab_champ[3].name);
		}
		draw_pl_heart(j, vm);
	}
}

void	print_logo3(int j, t_vm *vm)
{
	if (j >= 20 && j <= 25 && vm->nbr_next >= 1)
	{
		if (j == 20)
		{
			attron(COLOR_PAIR(vm->tab_champ[0].rgb));
			printw("%.16s", vm->tab_champ[0].name);
		}
		draw_pl_heart(j, vm);
	}
	if (j >= 26 && j <= 31 && vm->nbr_next >= 2)
	{
		if (j == 26)
		{
			attron(COLOR_PAIR(vm->tab_champ[1].rgb));
			printw("%.16s", vm->tab_champ[1].name);
		}
		draw_pl_heart(j, vm);
	}
	print_logo4(j, vm);
}

void	print_logo2(int j, t_vm *vm)
{
	if (j == 13)
		printw(" #############   ####  ############ ");
	if (j == 14)
		printw(" ###### ######  ####   ###### ####  ");
	if (j == 15)
		printw(" #####   ##### ##############  #### ");
	if (j == 16)
		printw(" ####     ########     ######   #### ");
	print_logo3(j, vm);
}

void	print_logo(int j, t_vm *vm)
{
	if (j == 0)
		printw("  #######                 ##########");
	if (j == 1)
		printw(" ####  ###                ###       ");
	if (j == 2)
		printw(" ###    ##                ###       ");
	if (j == 3)
		printw(" ###         ##### ##############   ");
	if (j == 4)
		printw(" ###       ###  ## ####   ###       ");
	if (j == 5)
		printw(" ###    ######  ######    ###       ");
	if (j == 6)
		printw(" ####  ### ###  ## ###    ###       ");
	if (j == 7)
		printw("  #######    ####  ###    ##########");
	if (j == 9)
		printw(" ###       ###       ##############  ");
	if (j == 10)
		printw(" ###   #   ###      #########   #### ");
	if (j == 11)
		printw(" ###  ###  ###     ##########    ### ");
	if (j == 12)
		printw(" ### ##### ###    #### ######   #### ");
	print_logo2(j, vm);
}
