/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_m_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:17:10 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:17:15 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_create_arena(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i].acb = 0;
		vm->arena[i].rgb = 11;
		vm->arena[i].asc_rgb = 11;
		vm->arena[i].flag = 0;
		vm->arena[i].o_acb = 0;
		vm->arena[i].hit = 0;
		vm->arena[i].pl = -666;
		vm->arena[i].bold = 0;
		i++;
	}
}

void	vm_init(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->tab_champ[i].weight = 0;
		vm->tab_champ[i].rgb = 1 + (i % 4);
		vm->tab_champ[i].id = -1;
		vm->tab_champ[i].nbr_process = 1;
		vm->tab_champ[i].alive = 0;
		vm->tab_champ[i].old_check = 0;
		vm->tab_champ[i].prev_live = 0;
		vm->tab_champ[i].lives_in_period = 0;		
	}
	vm->fd = 0;
	vm->dump_cycle = -1;
	vm->visual = 0;
	vm->nbr_next = 0;
	vm->last_check = 0;
	vm->total_lives_period = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_before_checking = CYCLE_TO_DIE;
	vm->lifes = 0;
	vm->win = 0;
	vm->total_process = 0;
	vm->aff = 0;
	vm->cycle = 0;
	vm->total_cycle = 0;
	vm->debug = 0;
	vm->cmd = NULL;
}

t_cmd		*add_list(t_vm *vm, int i)
{
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		lst->reg[0] = (vm->tab_champ[i].id * -1);
		lst->idx = vm->tab_champ[i].idx;//индекс первой  позиции курсора
		lst->pl = (vm->tab_champ[i].id * -1);
		lst->previdx = (vm->arena[lst->idx].acb) & 0xFF;//del?
		lst->rgb = 5 + (i % 4);//цвет каретки		
		lst->playing = 0;
		lst->wait = 0;
		lst->off = 0;
		lst->carry = 0;
		lst->life = 0;
		lst->nbr_process = vm->total_process + 1;
		lst->flag = 0;		
		lst->on = 1;
		lst->str_cycle = 0;
		lst->lnew = 0;
		lst->next = NULL;
		lst->prev = NULL;
		vm->total_process = lst->nbr_process;
	}	
	return (lst);
}

void	vm_load_lists(t_cmd **cmd, t_vm *vm)
{
	int		i;
	t_cmd	*tmp;
	//t_cmd	*tmp1;

	i = -1;
	while (++i < vm->nbr_next)
	{
		tmp = *cmd;
		if (tmp)
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = add_list(vm, i);
			//tmp->next->prev = *(cmd);
		}
		else
			*cmd = add_list(vm, i);
		// if (tmp)
		// {
		// 	tmp1 = add_list(vm, i);
		// 	tmp1->next = vm->cmd;
		// 	vm->cmd = tmp1;
		// }
		// else
		// 	*cmd = add_list(vm, i);
	}
}

void	vm_glow_cur(t_vm *vm, t_cmd *cmd)
{
	//while (cmd && !cmd->flag)
	while (cmd)
	{
		//ft_printf("vm_glow_cur id player|%d|\n", cmd->reg[0]);
		vm_next_step(vm, cmd, 0);
		cmd = cmd->next;
	}
}
