/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 02:27:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/18 02:27:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_cmd	*add_list(t_vm *vm)
{
	t_cmd		*lst;

	if ((lst = ft_memalloc(sizeof(t_cmd))))
	{
		lst->reg[0] = ID(PLAYER);
		lst->idx = IDX(PLAYER);//индекс первой  позиции курсора
		lst->rgb = 5 + ((int)PLAYER % 4);//цвет каретки
		lst->nbr_process = ON;
		//ft_printf("lst->idx |%d\n|", lst->idx);
	}
	else
		ft_error(vm, ERROR_MEMORY);
	return (lst);
}

void			vm_load_lists(t_vm *vm, t_cmd **cmd, t_cmd	*tmp)
{
	vm->current_player = 1;
	while (PLAYER < TOTAL_PLAYERS)
	{
		if ((tmp = *cmd))
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = add_list(vm);
			//tmp->next->flag = 1;
		}
		else
			*cmd = add_list(vm);
		vm->current_player++;
//		ft_printf("@@@ %d %d\n", ID(PLAYER), IDX(PLAYER));
	}
	vm->current_player = OFF;
}
