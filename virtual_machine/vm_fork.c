/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:49:39 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:49:45 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		fork_update_reg(int *dest, int *host)
{
	int		i;

	i = -1;
	while (++i < REG_NUMBER)
		dest[i] = host[i];
}

t_cmd		*fork_add_list(t_cmd *cmd1, int nb)
{
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		fork_update_reg(lst->reg, cmd1->reg);
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
		lst->lnew = 0;
		lst->zero = 0;
		lst->overlap = 0;
		lst->next = NULL;
	}
	return (lst);
}

int			vm_get_f_nbr(t_vm *vm, t_cmd *cmd1)
{
	short	two;

	two = 0xFF & vm->arena[mdx(cmd1->idx + 1)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd1->idx + 2)].acb;
	return (two % IDX_MOD);
}

void		vm_fork(t_vm *vm, t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*cmd1;
	int		two_val;
	int		id;

	cmd1 = NULL;
	tmp = NULL;
	cmd1 = *cmd;
	two_val = vm_get_f_nbr(vm, cmd1);
	if (cmd1)
	{
		tmp = fork_add_list(cmd1, vm->total_process + 1);
		if (vm->debug)
			ft_printf("|P\t%d| fork |%d| (%d)\n", cmd1->nbr_process,
				two_val, tmp->idx + two_val);
		id = vm_getpl(vm, tmp->pl * -1);
		if (id > -1)
			vm->tab_champ[id].nbr_process += 1;
		vm->total_process += 1;
		tmp->next = vm->cmd;
		vm->cmd = tmp;
	}
	vm_next_step(vm, *cmd, 3);
	vm_next_step(vm, tmp, two_val);
}
