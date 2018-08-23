/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_m_setrun_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:04:08 by amakhiny          #+#    #+#             */
/*   Updated: 2018/08/23 12:04:12 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			vm_dia(int nb)
{
	if (nb >= 0 && nb <= 15)
		return (1);
	return (0);
}

int			vm_len_len(int i, int acb, int idx, int len)
{
	while (i >= 0)
	{
		if ((acb >> (6 - i * 2) & 0x3) == REG_CODE)
			len += 1;
		else if ((acb >> (6 - i * 2) & 0x3) == DIR_CODE)
		{
			if (g_op_tab[idx].size)
				len += 2;
			else
				len += 4;
		}
		else if ((acb >> (6 - i * 2) & 0x3) == IND_CODE)
			len += 2;
		i--;
	}
	return (len);
}

int			vm_len_step(t_vm *vm, t_cmd *cmd, int idx)
{
	int		acb;
	int		i;
	int		len;

	len = 1;
	acb = vm->arena[mdx(cmd->idx + 1)].acb & 0xFF;
	if (!vm_dia(idx))
		return (1);
	i = g_op_tab[idx].nbr_args - 1;
	if (g_op_tab[idx].codage)
		len++;
	len = vm_len_len(i, acb, idx, len);
	return (len);
}

void		vm_set_cycle_wait(t_vm *vm, t_cmd *cmd)
{
	int		acb;

	acb = (vm->arena[mdx(cmd->idx)].acb & 0xFF) - 1;
	if (vm_its_cmd(vm, cmd))
	{
		cmd->overlap = 0;
		cmd->wait = g_op_tab[acb].cycles;
		cmd->playing = 1;
		cmd->zero = acb + 1;
		vm->arena[mdx(cmd->idx)].overlap = 0;
	}
	else
	{
		if (acb >= 0 && acb < 16)
		{
			cmd->overlap = 0;
			cmd->zero = acb + 1;
			cmd->wait = g_op_tab[acb].cycles;
			cmd->playing = 1;
		}
		else
			vm_next_step(vm, cmd, 1);
	}
}

void		vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		hex;
	int		zero;
	int		hit;

	hex = (vm->arena[mdx(cmd->idx)].acb & 0xFF);
	zero = cmd->zero;
	hit = -1;
	if (cmd->wait == 1)
	{
		if (vm_dia(zero - 1) && cmd->overlap == 0)
		{
			hit = 1;
			vm_cmd_triger(vm, cmd, zero);
		}
		else if (vm_cmd(vm, cmd, hex - 1))
		{
			hit = 1;
			cmd->overlap = 0;
			vm_cmd_triger(vm, cmd, hex);
		}
		if (hit == -1)
			vm_next_step(vm, cmd, 1);
		cmd->playing = 0;
	}
}
