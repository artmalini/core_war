/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_m_cycler_to_die.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:16:12 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:16:17 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	pl_res_all_proces(t_vm *vm)
{
	int i;

	i = -1;
	while (++i < vm->nbr_next)
		vm->tab_champ[i].nbr_process = 0;
}

void	pl_period_live(t_vm *vm)
{
	int i;

	i = -1;
	while (++i < vm->nbr_next)
		vm->tab_champ[i].lives_in_period = 0;
}

void	vm_curet_next(t_vm *vm, t_cmd *cmd)
{
	int     id;
	//(void)vm;
	while (cmd)
	{
		//if (!cmd->life && !cmd->off && cmd->on)
		if (!cmd->life && cmd->on)
		{
			id = vm_getpl(vm, cmd->pl * -1);
			if (id > -1 && vm->tab_champ[id].nbr_process > 0)
				vm->tab_champ[id].nbr_process--;
		}
		if (!cmd->life)
		{
			//if (vm->arena[mdx(cmd->idx)].rgb - 4 == cmd->rgb - 4)
			//	vm->arena[mdx(cmd->idx)].rgb -= 4;
			//ft_printf("|%d|", vm->cycle);
			cmd->off = 1;
			cmd->on = 0;
		}
		cmd->life = 0;
		cmd = cmd->next;
	}
}

void	vm_current_incr(t_cmd **cmd)
{
	t_cmd	*tmp1;
	t_cmd	*prev;

	tmp1 = *cmd;
	while (tmp1 && tmp1->off == 1)
	{
		*cmd = tmp1->next;
		free(tmp1);
		tmp1 = *cmd;
	} 
	while (tmp1)
	{
		while (tmp1 && tmp1->off != 1)
		{
			prev = tmp1;
			tmp1 = tmp1->next;
		}
		if (!tmp1)
			return ;
		prev->next = tmp1->next;
		free(tmp1);
		tmp1 = prev->next;
	}
}


void	vm_rev_pc(t_vm *vm, t_cmd *cmd)
{
	int		id;

	id = -1;
	while (cmd)
	{
		if (cmd->off && !cmd->on)
		{
			id = vm_getpl(vm, cmd->pl * -1);///////////////////////////////////////////////
			if (id > -1 && vm->tab_champ[id].nbr_process > 0)
			{
				vm->tab_champ[id].nbr_process--;
				cmd->nbr_process--;
				cmd->on = 1;
			}
		}
		cmd = cmd->next;
	}
}


void	vm_cycler_to_die(t_vm *vm, int *i)
{
	if (vm->cycle >= vm->cycle_to_die)
	{
		vm_curet_next(vm, vm->cmd);
		vm_current_incr(&vm->cmd);//should be for the performance
		//vm_rev_pc(vm, vm->cmd);
		if (vm->lifes == 0 || (vm->cycle_to_die) < 0)
		{
			*i = 0;
			pl_res_all_proces(vm);
			if (vm->total_cycle > 0)
				vm->win = 1;
			vm->cycle_to_die = 0;
		}
		vm->last_check++;
		if (vm->last_check == MAX_CHECKS || vm->lifes >= NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			if (vm->cycle_to_die < 0)
				vm->cycle_to_die = 0;
			vm->last_check = 0;
		}
		pl_period_live(vm);
		vm->cycle = 0;
		vm->lifes = 0;
	}
}
