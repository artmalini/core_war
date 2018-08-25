/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mng_func1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:17:49 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:17:53 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			mdx(int nbr)
{
	int		ret;

	ret = (nbr % MEM_SIZE < 0) ? nbr % MEM_SIZE + MEM_SIZE : nbr % MEM_SIZE;
	return (ret);
}

int			vm_pos_lcurs_cdg(t_vm *vm, t_cmd *cmd, int l, int bitln)
{
	int		i;

	i = 6;
	while (i > 0)
	{
		if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== REG_CODE)
			bitln += 1;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== DIR_CODE && l == 4)
			bitln += 4;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== DIR_CODE && l == 2)
			bitln += 2;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== IND_CODE)
			bitln += 2;
		i -= 2;
	}
	return (bitln);
}

int			vm_pos_curs(t_vm *vm, t_cmd *cmd)
{
	int		bitln;
	int		l;

	bitln = 1;
	if (g_op_tab[vm->arena[cmd->idx].acb - 1].size == 0)
		l = 4;
	if (g_op_tab[vm->arena[cmd->idx].acb - 1].size == 1)
		l = 2;
	if (g_op_tab[vm->arena[cmd->idx].acb - 1].codage != 0)
		bitln += 1;
	return (vm_pos_lcurs_cdg(vm, cmd, l, bitln));
}

void		vm_winner(t_vm *vm)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (vm->win)
	{
		while (++i < vm->nbr_next)
		{
			if (vm->tab_champ[i].prev_live >= vm->tab_champ[j].prev_live)
				j = i;
		}
		if (vm->total_cycle > 1)
		{
			if (vm->total_cycle - vm->tab_champ[j].prev_live == 1)
				vm->total_cycle--;
		}
		if (!vm->visual)
			ft_printf("Player %d (%s) won\n",
				vm->tab_champ[j].id, vm->tab_champ[j].name);
	}
}

void		vm_next_step(t_vm *vm, t_cmd *cmd, int pos)
{
	int		i;
	int		tm;
	int		acb;

	if (vm->arena[cmd->idx].flag > 0)
		vm->arena[cmd->idx].flag--;
	tm = cmd->idx;
	i = cmd->idx + pos;
	cmd->idx = mdx(i);
	acb = vm->arena[mdx(cmd->idx)].acb & 0xFF;
	if ((acb > 0 && acb < 17) && cmd->overlap == 0)
		cmd->zero = acb;
	else
	{
		cmd->overlap = 1;
		cmd->zero = 0;
	}
	vm->arena[cmd->idx].flag++;
	vm->arena[cmd->idx].rgb = cmd->rgb;
	if (vm->arena[tm].flag == 0)
		vm->arena[tm].rgb = vm->arena[tm].asc_rgb;
}
