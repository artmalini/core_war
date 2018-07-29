/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:51:02 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:51:15 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		lfork_update_reg(int *dest, int *host)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
		dest[i] = host[i];
}

t_cmd		*lfork_add_list(t_vm *vm, t_cmd *cmd1, int nb)
{
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		lfork_update_reg(lst->reg, cmd1->reg);
		lst->idx = cmd1->idx;
		lst->pl = vm->arena[cmd1->idx].pl;
		lst->previdx = cmd1->previdx;
		lst->rgb = cmd1->rgb;
		lst->playing = 0;
		lst->wait = 0;
		lst->off = cmd1->off;
		lst->carry = cmd1->carry;
		lst->life = cmd1->life;
		lst->nbr_process = nb;
		lst->on = 0;
		lst->str_cycle = cmd1->str_cycle;// + op_tab[vm->arena[mdx(cmd1->idx)].acb - 1].cycles;
		lst->flag = 0;
		lst->lnew = 1;
		lst->next = NULL;
		lst->prev = NULL;
	}	
	return (lst);
}

void	vm_lfork(t_vm *vm, t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*cmd1;

	//t_cmd	*base;
	short	two;
	int		id;
	//int		two_val;


	cmd1 = NULL;
	tmp = NULL;
	cmd1 = *cmd;	
	two = 0xFF & vm->arena[mdx(cmd1->idx + 1)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd1->idx + 2)].acb;
	//two_val = (two % IDX_MOD);
	//base = vm->cmd;
	if (cmd1)
	{
		tmp = lfork_add_list(vm, cmd1, vm->total_process + 1);
		if (vm->debug)
			ft_printf("|P\t%d| lfork |%d| (%d)\n", cmd1->nbr_process, two, tmp->idx + two);

		id = vm_getpl(vm, tmp->pl * -1);
		if (id > -1)
			vm->tab_champ[id].nbr_process += 1;
		vm->total_process += 1;
		// while (cmd1->next != NULL)
		// 	cmd1 = cmd1->next;
		// cmd1->next = tmp;
		// tmp->prev = cmd1;

		tmp->next = vm->cmd;
		vm->cmd = tmp;

		// if (base != NULL)
		// 	base->prev = tmp;
		// tmp->next = vm->cmd;
		// vm->cmd = tmp;
	}

	vm_next_step(vm, *cmd, 3);
	vm_next_step(vm, tmp, two);
}
