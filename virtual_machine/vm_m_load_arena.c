/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_m_load_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:17:31 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:17:34 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_play_arena(t_vm *vm)
{
	if (vm->dump_cycle > -1)
	{
		if (vm->total_cycle == vm->dump_cycle)
			vm_dump_arena(vm);
	}
	else if (vm->visual)
		vm_vis_arena(vm);
}

void		vm_decr(t_vm *vm, t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->playing)
			cmd->wait -= 1;
		cmd = cmd->next;
	}
	vm->cycle++;
	vm->total_cycle++;
}

void		vm_sleep(t_vm *vm, int *pause, int *nb, int entry)
{
	if (vm->visual)
	{
		nodelay(stdscr, 1);
		entry = getch();
		if (entry && vm->win == 1)
			vm->win = -1;
		else if (entry == 66)
		{
			if (*nb == 150000)
				*nb = 150;
			else
				*nb = 150000;
		}
		else if (entry == 32)
		{
			if (*pause == 1)
				*pause = 0;
			else
				*pause = 1;
		}
		nodelay(stdscr, 0);
		usleep(*nb);
	}
}

void		vm_arena_cnt(t_vm *vm, int *i)
{
	t_cmd	*c;

	c = vm->cmd;
	vm_decr(vm, vm->cmd);
	while (c)
	{
		if (!c->off)
		{
			if (!c->playing)
				vm_set_cycle_wait(vm, c);
			else
				vm_run_waiting_cycle(vm, c);
		}
		if (c->next == NULL)
			vm_cycler_to_die(vm, i);
		c = c->next;
	}
}

void		vm_load_arena(t_vm *vm)
{
	int		i;
	int		pause;
	int		nb;

	nb = 150000;
	i = 1;
	pause = 1;
	if (vm->visual)
		if (system("pgrep -x afplay") != -1)
			system("afplay ./resourses/Heroes.mp3&");
	while (i)
	{
		if (pause)
		{
			vm_arena_cnt(vm, &i);
			vm_play_arena(vm);
			if (vm->dump_cycle > -1 && (vm->dump_cycle == vm->total_cycle))
				i = 0;
		}
		vm_sleep(vm, &pause, &nb, 0);
	}
}
