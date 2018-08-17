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
	int		i;

	i = -1;
	while (++i < REG_NUMBER)
		dest[i] = host[i];
}

t_cmd		*lfork_add_list(t_cmd *cmd1, int nb)
{
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		lfork_update_reg(lst->reg, cmd1->reg);
		lst->idx = cmd1->idx;
		lst->pl = cmd1->pl;
		lst->rgb = cmd1->rgb;
		lst->playing = 0;
		lst->wait = 0;
		lst->off = cmd1->off;
		lst->carry = cmd1->carry;
		lst->life = cmd1->life;
		lst->nbr_process = nb;
		lst->flag = 0;
		lst->on = 1;
		lst->lnew = cmd1->lnew;
		lst->zero = 0;
		lst->overlap = 0;
		lst->next = NULL;
	}
	return (lst);
}

int			vm_get_lf_nbr(t_vm *vm, t_cmd *cmd1)
{
	int		two;

	two = 0xFF & vm->arena[mdx(cmd1->idx + 1)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd1->idx + 2)].acb;
	return (two);
}

void		vm_lfork(t_vm *vm, t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*cmd1;
	int		two;
	int		id;

	cmd1 = NULL;
	tmp = NULL;
	cmd1 = *cmd;
	two = vm_get_lf_nbr(vm, cmd1);
	if (cmd1)
	{
		tmp = lfork_add_list(cmd1, vm->total_process + 1);
		if (vm->debug)
			ft_printf("|P\t%d| lfork |%d| (%d)\n", cmd1->nbr_process,
				two, tmp->idx + two);
		id = vm_getpl(vm, tmp->pl * -1);
		if (id > -1)
			vm->tab_champ[id].nbr_process += 1;
		vm->total_process += 1;
		tmp->next = vm->cmd;
		vm->cmd = tmp;
	}
	vm_next_step(vm, *cmd, 3);
	vm_next_step(vm, tmp, two);
}
