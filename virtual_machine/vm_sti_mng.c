/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sti_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:19:10 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:19:14 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			vm_rdd_sti(t_vm *vm, t_cmd *cmd)
{
	int		res;
	short	arg1;
	short	arg2;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
	res = (arg1 + arg2);
	return (res);
}

int			vm_rir_sti(t_vm *vm, t_cmd *cmd)
{
	int		res;
	int		arg1;
	int		arg2;
	short	dir;
	int		dir1;
	
	res = 0;
	dir = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	dir <<= 8;
	dir += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	dir1 = (dir % IDX_MOD);
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + dir1)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 1)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 2)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 3)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	if (vm_v_cmd(arg2 - 1, arg2 - 1, arg2 - 1))
		res = (arg1 + cmd->reg[arg2 - 1]);
	return (res);
}

int			vm_rrd_sti(t_vm *vm, t_cmd *cmd)
{
	int		res;
	int		arg1;
	short	arg2;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	if (vm_v_cmd(arg1 - 1, arg1 - 1, arg1 - 1))
		res = (cmd->reg[arg1 - 1] + arg2);
	return (res);
}

int			vm_rrr_sti(t_vm *vm, t_cmd *cmd)
{
	int		res;
	int		arg1;
	int		arg2;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm_v_cmd(arg1 - 1, arg1 - 1, arg2 - 1))
		res = (cmd->reg[arg1 - 1] + cmd->reg[arg2 - 1]);
	return (res);
}

int			vm_rid_sti(t_vm *vm, t_cmd *cmd)
{
	int		res;
	short	arg1;
	short	dir;
	int		arg2;
	int		dir1;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	dir1 = (arg1 % IDX_MOD);
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + dir1)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 1)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 2)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 3)].acb;
	dir = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	dir <<= 8;
	dir += 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
	res = (arg2 + dir);
	return (res);
}
