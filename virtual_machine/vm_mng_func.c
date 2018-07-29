/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mng_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:53:20 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/26 15:53:24 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		mdx(int nbr)
{
	int		ret;

	ret = (nbr % MEM_SIZE < 0) ? (nbr % MEM_SIZE + MEM_SIZE) : nbr % MEM_SIZE;
	return (ret);
}

int		vm_pos_curs(t_vm *vm, t_cmd *cmd)
{
	int		i;
	int		bitln;
	int		l_size;

	bitln = 1;
	if (op_tab[vm->arena[cmd->idx].acb - 1].size == 0)
		l_size = 4;
	if (op_tab[vm->arena[cmd->idx].acb - 1].size == 1)
		l_size = 2;
	if (op_tab[vm->arena[cmd->idx].acb - 1].codage != 0)
		bitln += 1;
	i = 6;
	while (i > 0)
	{
		if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == REG_CODE)
			bitln += 1;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == DIR_CODE && l_size == 4)
			bitln += 4;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == DIR_CODE && l_size == 2)
			bitln += 2;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == IND_CODE)
			bitln += 2;
		i -= 2;
	}
	return (bitln);
}

int		vm_v_cmd(int a, int b, int c)
{
	if (a < 0 || a >= REG_NUMBER ||	
		b < 0 || b >= REG_NUMBER ||
		c < 0 || c >= REG_NUMBER)
		return (0);
	return (1);
}

int		get_indir_arg(t_vm *vm, t_cmd *cmd, int nb)
{
	unsigned int	one;

	one = 0xFF & vm->arena[mdx(cmd->idx + nb)].acb;
	one <<= 8;
	one += 0xFF & vm->arena[mdx(cmd->idx + nb + 1)].acb;
	one <<= 8;
	one += 0xFF & vm->arena[mdx(cmd->idx + nb + 2)].acb;
	one <<= 8;
	one += 0xFF & vm->arena[mdx(cmd->idx + nb + 3)].acb;
	return ((int)one);
}

int		vm_direct(t_vm *vm, t_cmd *cmd, int *arg)
{
	unsigned int	one;
	unsigned short	two;

	one = 0;
	if (arg[4] == 4)
	{
		one = 0xFF & vm->arena[mdx(cmd->idx + arg[3])].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 1)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 2)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 3)].acb;
		return ((int)one);
	}
	else if (arg[4] == 2)
	{
		two = 0xFF & vm->arena[mdx(cmd->idx + arg[3])].acb;
		two <<= 8;
		two += 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 1)].acb;
		return ((short)two);
	}
	return (one);
}

int		vm_indir(t_vm *vm, t_cmd *cmd, int nb)
{
	int				ret;
	unsigned short	two;

	two = 0xFF & vm->arena[mdx(cmd->idx + nb)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd->idx + nb + 1)].acb;
	ret = get_indir_arg(vm, cmd, (short)two);
	return (mdx(ret));
}
