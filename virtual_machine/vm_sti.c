/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:54:15 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:54:19 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 84  == (T_REG, T_REG, T_REG)
** 88  == (T_REG, T_REG, T_DIR)
** 100 == (T_REG, T_DIR, T_REG)
** 104 == (T_REG, T_DIR, T_DIR)
** 116 == (T_REG, T_IND, T_REG)
** 120 == (T_REG, T_IND, T_DIR)
*/

void	vm_sti_step(t_vm *vm, t_cmd *cmd, int cdg)
{ 
	if (cdg == 104)
		vm_next_step(vm, cmd, 7);
	else if (cdg == 84)
		vm_next_step(vm, cmd, 5);
	else if (cdg == 88 || cdg == 100)
		vm_next_step(vm, cmd, 6);
	else if (cdg == 120)
		vm_next_step(vm, cmd, 9);
	else if (cdg == 116)
		vm_next_step(vm, cmd, 8);
}

void	load_res(t_vm *vm, t_cmd *cmd, int direct)
{
	int		i;
	int		reg1;
	int		dat;
	//int		hit;

	i = -1;
	reg1 =  0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	if (!(reg1 > 0 && reg1 < 16))
		return ;
	dat = cmd->reg[reg1 - 1];
	//hit = 1;
	while (++i <= 3)
	{
		vm->arena[mdx(cmd->idx + direct + i)].acb = ((dat) >> ((3 - i) * 8)) & 0xFF;
		//vm->arena[mdx(cmd->idx + direct + i)].o_acb = ((dat) >> ((3 - i) * 8)) & 0xFF;
		//vm->arena[mdx(cmd->idx + direct + i)].hit = ((hit) >> ((3 - i) * 8)) & 0xFF;
		vm->arena[mdx(cmd->idx + direct + i)].rgb = cmd->rgb - 4;
		vm->arena[mdx(cmd->idx + direct + i)].asc_rgb = cmd->rgb - 4;
	}
	if (vm->debug)
	{
		ft_printf("|P\t%d| sti |%d| |r%d|\n\t\t (with pc and mod %d)total_cycle|%d|\n",
			cmd->nbr_process, direct, reg1, cmd->idx + direct, vm->total_cycle);
	}
}

int			vm_rdr_sti(t_vm *vm, t_cmd *cmd)
{
	int		res;
	int		arg1;
	short	arg2;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;	
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	if (vm_v_cmd(arg2 - 1, arg2 - 1, arg2 - 1))
		res = (arg1 + cmd->reg[arg2 - 1]);
	return (res);
}

void	vm_sti(t_vm *vm, t_cmd *cmd)
{
	int		cdg;
	int		direct;

	direct = 0;
	cdg = (0xFF & vm->arena[mdx(cmd->idx + 1)].acb);
	if (cdg == 100 || cdg == 104 || cdg == 84 ||
		cdg == 88 || cdg == 120 || cdg == 116)
	{
		if (cdg == 88)
			direct = vm_rrd_sti(vm, cmd);
		else if (cdg == 84)
			direct = vm_rrr_sti(vm, cmd);
		else if (cdg == 100)
			direct = vm_rdr_sti(vm, cmd);
		else if (cdg == 104)
			direct = vm_rdd_sti(vm, cmd);
		else if (cdg == 120)
			direct = vm_rid_sti(vm, cmd);
		else if (cdg == 116)
			direct = vm_rir_sti(vm, cmd);
		load_res(vm, cmd, (direct % IDX_MOD));
		vm_sti_step(vm, cmd, cdg);
	}
}
