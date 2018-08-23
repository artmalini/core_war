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

void		vm_zero_reg(int *dest)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
		dest[i] = 0;
}

t_cmd		*add_list(t_vm *vm, int i)
{
	t_cmd	*lst;

	if (!(lst = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	vm_zero_reg(lst->reg);
	lst->reg[0] = (vm->tab_champ[i].id * -1);
	lst->idx = vm->tab_champ[i].idx;
	lst->pl = (vm->tab_champ[i].id * -1);
	lst->rgb = 5 + (i % 4);
	lst->playing = 0;
	lst->wait = 0;
	lst->off = 0;
	lst->carry = 0;
	lst->life = 0;
	lst->nbr_process = vm->total_process + 1;
	lst->flag = 0;
	lst->on = 1;
	lst->lnew = 0;
	lst->zero = 0;
	lst->overlap = 0;
	lst->next = NULL;
	vm->total_process = lst->nbr_process;
	return (lst);
}

void		vm_load_lists(t_cmd **cmd, t_vm *vm)
{
	int		i;
	t_cmd	*tmp;
	t_cmd	*tmp1;

	i = -1;
	while (++i < vm->nbr_next)
	{
		tmp = *cmd;
		if (tmp)
		{
			tmp1 = add_list(vm, i);
			tmp1->next = *cmd;
			*cmd = tmp1;
		}
		else
			*cmd = add_list(vm, i);
	}
}

void		vm_glow_cur(t_vm *vm, t_cmd *cmd)
{
	while (cmd)
	{
		vm_next_step(vm, cmd, 0);
		cmd = cmd->next;
	}
}
