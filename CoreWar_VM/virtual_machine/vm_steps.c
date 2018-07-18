/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 02:18:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/18 02:18:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_next_step(t_vm *vm, t_cmd *cmd, int pos)
{
	int		i;
	int		tm;

	if (vm->arena[cmd->idx].flag > 0)
		vm->arena[cmd->idx].flag--;
	tm = cmd->idx;
	i = cmd->idx + pos;
	cmd->idx = (i % MEM_SIZE < 0) ? (i % MEM_SIZE + MEM_SIZE) : i % MEM_SIZE;
	//ft_printf("cmd->idx |%d| ", cmd->idx);
	//ft_printf("cmd->idx %d ", vm->arena[cmd->idx]);
	//refresh();
	// erase();
	// attron(COLOR_PAIR(11));
	// printw("vm_next_step |%d|\n", vm->arena[cmd->idx].flag);
	// refresh();
	vm->arena[cmd->idx].flag++;
	vm->arena[cmd->idx].rgb = cmd->rgb;
	if (vm->arena[tm].flag == 0)
		vm->arena[tm].rgb = vm->arena[tm].asc_rgb;

}


int			vm_step_shift(int type, int label_size)
{
	if (type == REG_CODE)
		return (1);
	else if (type == DIR_CODE)
		return (2 + 2 * (1 - label_size));
	else if (type == IND_CODE)
		return (2);
	else
		return (0);
}

int			vm_calc_steps(int hex, int pos)
{
	int		param;
	int		ret;

	ret = 0;
	param = (op_tab[hex].nbr_args);
	//printw("param |%d|\n", param);
	//refresh();
	if (hex < 1 || hex > 16)
		return (1);
	ret = vm_step_shift((pos >> 6) & 3, op_tab[hex].size);
	if (param > 1)
		ret += vm_step_shift((pos >> 4) & 3, op_tab[hex].size);
	if (param > 2)
		ret += vm_step_shift((pos >> 2) & 3, op_tab[hex].size);
	//printw("ret |%d|\n", ret);
	//refresh();
	return (ret + 2);
}