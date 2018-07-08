/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 12:21:22 by tvertohr          #+#    #+#             */
/*   Updated: 2018/07/08 12:21:24 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	and(t_vm *vm, t_proc *proc)
{
	int	arg[3];

	arg[0] = 0;
	arg[1] = 0;
	arg[2] = 0;
	param_op(vm, proc, arg);
}

static void	choose_op(int *arg, t_proc *proc)
{
	if (proc->instruction == 6)
		proc->reg[arg[2] - 1] = arg[0] & arg[1];
	else if (proc->instruction == 7)
		proc->reg[arg[2] - 1] = arg[0] | arg[1];
	else if (proc->instruction == 8)
		proc->reg[arg[2] - 1] = arg[0] ^ arg[1];
	if (proc->reg[arg[2] - 1] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}

static void	param_op_2(t_vm *vm, t_proc *proc, int *arg, int *pc)
{
	if (PARAM2 == REG)
	{
		arg[1] = get_reg(vm, pc);
		if (!(is_reg(arg[1])))
			return ;
		arg[1] = proc->reg[arg[1] - 1];
	}
	else if (PARAM2 == INDIRECT)
	{
		arg[1] = (short)get_ind(vm, pc);
		arg[1] %= IDX_MOD;
		arg[1] = get_value(vm, mod(proc->save_pc + arg[1], MEM_SIZE));
	}
	else if (PARAM2 == DIRECT)
		arg[1] = get_dir(vm, pc, proc->instruction);
	arg[2] = get_reg(vm, pc);
	if (!is_reg(arg[2]))
		return ;
	choose_op(arg, proc);
	proc->pc = *pc;
}

int	is_reg(int value)
{
	if (value > 0 && value < REG_NUMBER)
		return (1);
	return (0);
}

int	get_reg(t_vm *vm, int *i)
{
	int	reg;

	reg = 0;
	reg = (unsigned char)vm->arena[(*i) % MEM_SIZE];
	(*i)++;
	return (reg);
}

int	get_ind(t_vm *vm, int *i)
{
	int	ind;

	ind = 0;
	ind += (unsigned char)vm->arena[(*i) % MEM_SIZE];
	ind <<= 8;
	ind += (unsigned char)vm->arena[((*i) + 1) % MEM_SIZE];
	{
		(*i) += 2;
	}
	return (ind);
}

long int		get_value(t_vm *vm, int index)
{
	long int	value;

	value = 0;
	value = (unsigned char)vm->arena[mod(index, MEM_SIZE)];
	value <<= 8;
	value += (unsigned char)vm->arena[mod(index + 1, MEM_SIZE)];
	value <<= 8;
	value += (unsigned char)vm->arena[mod(index + 2, MEM_SIZE)];
	value <<= 8;
	value += (unsigned char)vm->arena[mod(index + 3, MEM_SIZE)];
	return (value);
}

int	mod(int a, int b)
{
	if (a % b >= 0)
		return (a % b);
	return ((a % b) + b);
}

int	get_dir(t_vm *vm, int *i, int op_code)
{
	int	dir;
	int	j;

	j = 0;
	dir = 0;
	if (op_code == 9 || op_code == 10 || op_code == 11 || op_code == 12 ||
			op_code == 14 || op_code == 15)
	{
		dir += (unsigned char)vm->arena[(*i) % MEM_SIZE];
		dir <<= 8;
		dir += (unsigned char)vm->arena[((*i) + 1) % MEM_SIZE];
		(*i) += 2;
	}
	else
	{
		while (j < 4)
		{
			dir += (unsigned char)vm->arena[(j + (*i)) % MEM_SIZE];
			if (j != 3)
				dir <<= 8;
			j++;
		}
		(*i) += 4;
	}
	return (dir);
}

void		param_op(t_vm *vm, t_proc *proc, int *arg)
{
	int	pc;

	proc->pc++;
	pc = proc->pc + 1;
	if (PARAM1 == REG)
	{
		arg[0] = get_reg(vm, &pc);
		if (!is_reg(arg[0]))
			return ;
		arg[0] = proc->reg[arg[0] - 1];
	}
	else if (PARAM1 == INDIRECT)
	{
		arg[0] = (short)get_ind(vm, &pc);
		arg[0] %= IDX_MOD;
		arg[0] = get_value(vm, mod(proc->save_pc + arg[0], MEM_SIZE));
	}
	else if (PARAM1 == DIRECT)
		arg[0] = get_dir(vm, &pc, proc->instruction);
	param_op_2(vm, proc, arg, &pc);
}
