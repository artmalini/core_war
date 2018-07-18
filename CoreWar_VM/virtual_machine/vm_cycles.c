/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cycles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 01:46:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/18 01:46:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		pl_period_live(t_vm *vm)
{
	int 	i;

	i = -1;
	while (++i < vm->nbr_next)
		vm->tab_champ[i].lives_in_period = 0;
}

void		vm_curet_next(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->life)
		{
			cmd->flag = 1;
		}
		cmd->life = 0;
		cmd = cmd->next;
	}
}

int			vm_has_cmd(t_vm *vm, t_cmd *cmd)
{
	int 	i;

	i = vm->arena[cmd->idx].acb & 0xFF;
	//i -= 1;
	// erase();
	// attron(COLOR_PAIR(11));
	//printw("vm_has_cmd |%d|\n", i);
	//refresh();
	if (i > 0 && i < 17)
		return (i);
	else
		return (0);
}

void		vm_cycler_todie(t_vm *vm, int *i)
{
	//vm_curet_next(vm->cmd);
	if (vm->lifes == 0 || (vm->cycle_to_die - CYCLE_DELTA) < 1)
		*i = 0;
	if (vm->lifes < NBR_LIVE)
		vm->last_check += 1;
	if (vm->last_check == MAX_CHECKS || vm->lifes >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->cycle_to_die < 0)
		{
			vm_curet_next(vm->cmd);
			vm->cycle_to_die = 0;
		}
		vm->lifes = 0;
		vm->last_check = 0;
	}
	pl_period_live(vm);
	vm->cycle = 0;
	//vm->lifes = 0;
}

void		vm_cycler_to_die(t_vm *vm, int *i)
{
	if (vm->cycle == vm->cycle_to_die)
	{
		//cmd->flag = 0;
		vm_cycler_todie(vm, i);
	}
		//	vm_switch_cursor(cmd);
	else
	{
		vm->cycle++;
		vm->total_cycle++;
	}
}

void		vm_set_cycle_wait(t_vm *vm, t_cmd *cmd)
{
	int		i;
	//ft_printf("ok\n");
	if ((i = vm_has_cmd(vm, cmd)) != 0)
	{
		cmd->playing = 1;
		cmd->wait = op_tab[i - 1].cycles;
		//ft_printf("ok %d\n", cmd->wait);
		//vm_next_step(vm, cmd, 1);
		//
		//printw("%s %d\n", op_tab[i].name, op_tab[i].cycles);
		//refresh();
	}
	else
		vm_next_step(vm, cmd, 1);
}
