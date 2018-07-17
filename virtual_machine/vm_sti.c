
#include "vm.h"

/*
** 84  == (T_REG, T_REG, T_REG)
** 88  == (T_REG, T_REG, T_DIR)
** 104 == (T_REG, T_DIR, T_DIR)
** 116 == (T_REG, T_IND, T_REG)
** 120 == (T_REG, T_IND, T_DIR)
*/

void	load_res(t_vm *vm, t_cmd *cmd, int direct)
{
	int		i;
	int		val;
	int		dat;

	i = -1;
	val = (0xFF & vm->arena[mdx(cmd->idx + 2)].acb);
	if (val < 0 && val >= REG_NUMBER)
		return ;
	dat = cmd->reg[val - 1];
	while (++i <= 3)
	{
		vm->arena[mdx(cmd->idx + direct + i)].acb = ((dat * -1) >> ((3 - i) * 8)) & 0xFF;
		vm->arena[mdx(cmd->idx + direct + i)].rgb = cmd->rgb - 4;
		vm->arena[mdx(cmd->idx + direct + i)].asc_rgb = cmd->rgb - 4;
		//vm->arena[mdx(direct + i)].acb = ((cmd->reg[0] * -1) >> ((3 - i) * 8)) & 0xFF;
	}
	//ft_printf("sti |%d| value|%d| jump|%d|\n", direct, dat, vm_pos_curs(vm, cmd));
}

int		vm_rdd_sti(t_vm *vm, t_cmd *cmd)
{
	//int		pc;
	int		res;
	short	arg1;
	short	arg2;
	
	res = 0;
	//pc = 0xFF & (vm->arena[mdx(cmd->idx + 2)].acb);
	//pc = (cmd->idx - 1) + (0xFF & vm->arena[mdx(cmd->idx + 2)].acb);
	//ft_printf("PC %d %d\n", pc, vm->arena[mdx(cmd->idx + 2)].acb);
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;

	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
	//res = cmd->reg[pc - 1] + ((arg1 + arg2) % IDX_MOD);
	res = (arg1 + arg2);
	//ft_printf("sti arg1|%d| arg2|%d| %d\n", arg1, arg2, res);
	return (res);
}

int		vm_rir_sti(t_vm *vm, t_cmd *cmd)
{
	int				res;
	int				arg1;
	short			arg2;
	short			dir;
	int				dir1;
	
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
	res = (arg1 + arg2);
	return (res);
}

int		vm_rrd_sti(t_vm *vm, t_cmd *cmd)
{
	int				res;
	int				arg1;
	short			arg2;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;

	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	res = (arg1 + arg2);
	return (res);
}

int		vm_rrr_sti(t_vm *vm, t_cmd *cmd)
{
	int		res;
	int	arg1;
	int	arg2;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	res = (arg1 + arg2);
	return (res);
}

int		vm_rid_sti(t_vm *vm, t_cmd *cmd)
{
	int				res;
	short			arg1;
	short			dir;
	int				arg2;
	int				dir1;
	
	res = 0;
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	dir = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	dir <<= 8;
	dir += 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
	dir1 = (dir % IDX_MOD);
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + dir1)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 1)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 2)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + dir1 + 3)].acb;
	res = (arg1 + arg2);
	return (res);
}

void	vm_sti(t_vm *vm, t_cmd *cmd)
{
	int		cdg;
	int		direct;

	direct = 0;
	cdg = (0xFF & vm->arena[mdx(cmd->idx + 1)].acb);
	if (cdg == 104 || cdg == 84 || cdg == 88 || cdg == 120 || cdg == 116)
	{
		if (cdg == 104)
			direct = vm_rdd_sti(vm, cmd);
		else if (cdg == 84)
			direct = vm_rrr_sti(vm, cmd);
		else if (cdg == 88)
			direct = vm_rrd_sti(vm, cmd);
		else if (cdg == 120)
			direct = vm_rid_sti(vm, cmd);
		else if (cdg == 116)
			direct = vm_rir_sti(vm, cmd);
		load_res(vm, cmd, direct);
		vm->arena[mdx(cmd->idx)].rgb = cmd->rgb - 5;
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
}
