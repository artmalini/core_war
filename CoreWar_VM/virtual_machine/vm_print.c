/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 14:36:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/03 14:36:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// void	draw_dead_pl(int j)
// {
// ##  ### ##
// # #  #  # #
// ##   #  ##
// # #  #  #
// # # ### #
// }

void		vm_dump_arena(t_vm *vm)
{
	int		i;
	int		mem;

	mem = 64;
	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", 0xFF & vm->arena[i].acb);
		if ((i + 1) % 64 == 0)
		{
			mem += 64;
			if (i + 1 < MEM_SIZE)
			{
				ft_printf("\n");
				ft_printf("%#06x : ", mem);
			}
		}
		i++;
	}
	ft_printf("\n");
}

void		draw_pl_heart(int j)
{
	attron(COLOR_PAIR(1));
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

void		print_header2(int j, t_vm *vm)
{
	if (j == 13)
		printw(" #############   ####  ############ ");
	if (j == 14)
		printw(" ###### ######  ####   ###### ####  ");
	if (j == 15)
		printw(" #####   ##### ##############  #### ");
	if (j == 16)
		printw(" ####     ########     ######   #### ");
	if (j >= 20 && j <= 25 && vm->nbr_next >= 1)
	{
		if (j == 20)
		{
			attron(COLOR_PAIR(vm->tab_champ[0].rgb));
			printw("%.16s", vm->tab_champ[0].name);
		}
		draw_pl_heart(j);
	}
	if (j >= 26 && j <= 31 && vm->nbr_next >= 2)
	{
		if (j == 26)
		{
			attron(COLOR_PAIR(vm->tab_champ[1].rgb));
			printw("%.16s", vm->tab_champ[1].name);
		}
		draw_pl_heart(j);
	}
	if (j >= 32 && j <= 37 && vm->nbr_next >= 3)
	{
		if (j == 32)
		{
			attron(COLOR_PAIR(vm->tab_champ[2].rgb));
			printw("%.16s", vm->tab_champ[2].name);
		}
		draw_pl_heart(j);
	}
	if (j >= 38 && j <= 43 && vm->nbr_next == 4)
	{
		if (j == 38)
		{
			attron(COLOR_PAIR(vm->tab_champ[3].rgb));
			printw("%.16s", vm->tab_champ[3].name);
		}
		draw_pl_heart(j);
	}
}

void		print_header(int j, t_vm *vm)
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
	print_header2(j, vm);
}

int			vm_usage(void)
{
	ft_printf("usage : ./corewar [-dump nbr_cycles]"
					  "[[-n number] champion1.cor] ...\n");
	exit(1);
	return (0);
}