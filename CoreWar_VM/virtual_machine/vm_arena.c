/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 01:34:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/18 01:34:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_glow_cur(t_vm *vm, t_cmd *cmd)
{
	//while (cmd && !cmd->flag)
	while (cmd)
	{
		//ft_printf("vm_glow_cur id player|%d|\n", cmd->reg[0]);
		vm_next_step(vm, cmd, 0);
		cmd = cmd->next;
	}
}

void		vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		pos;
	int		hex;

	hex = vm->arena[cmd->idx].acb;
	if (cmd->wait == 0)
	{
		if (vm_its_cmd(vm, cmd))
			vm_cmd_triger(vm, cmd, hex);
		else
		{
			pos = vm->arena[cmd->idx + 1].acb;
			vm_next_step(vm, cmd, vm_calc_steps(hex, pos));
		}
		//printw("%d %d\n", pos, hex);
		//refresh();
		cmd->playing = 0;
	}
	else
		cmd->wait -= 1;
}

void		vm_play_arena(t_vm *vm)
{
	erase();
	vm_game_stat(vm);
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (i < MEM_SIZE)
	{
		//printw(" ");
		//if (vm->arena[i].bold > 0)
		//	attron(A_BOLD);
		attron(COLOR_PAIR(vm->arena[i].rgb));
		printw("%02x ", 0xFF & vm->arena[i].acb);
		//attroff(COLOR_PAIR(vm->arena[i].rgb));
		// if (vm->arena[i].bold > 0)
		// {
		// 	attroff(A_BOLD);
		// 	vm->arena[i].bold -= 1;
		// }
		if ((i + 1) % 64 == 0)
		{
			//mem += 64;
			//if (i + 1 < MEM_SIZE)
			attron(COLOR_PAIR(2));
			print_header(++j, vm);
			printw("\n");
		}
		i++;
	}
	printw("\n");
	refresh();
}

void		vm_create_arena(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i].acb = 0;
		vm->arena[i].rgb = 11;
		vm->arena[i].asc_rgb = 11;
		vm->arena[i].flag = 0;
		//vm->arena[i].bold = 0;
		i++;
	}
}

void		vm_load_arena(t_vm *vm)
{
	int		i;
	t_cmd	*c;


	i = 1;
	vm_load_ncurses();

	//vm_dump_arena(vm);
	//while (++i < 2)
	//	vm_play_arena(vm);
	while (i)
	{
		c = vm->cmd;
		//vm_play_arena();
		vm_play_arena(vm);
		while (c)
		{
			if (!c->flag)
				vm_cycler_to_die(vm, &i);
			//else
			//{
			if (!c->off)
			{
				if (!c->playing)
				{
					vm_set_cycle_wait(vm, c);
					//printw("%d\n", c->wait);
					//refresh();
				}
				else
					vm_run_waiting_cycle(vm, c);
			}

			//}
			//printw("%d\n", c->wait);
			//refresh();
			c = c->next;
		}
	}

	getch();
	endwin();
}
