
#include "vm.h"

void	load_res(t_vm *vm, t_cmd *cmd, int direct)
{
	int		i;

	i = -1;
	while (++i <= 3)
	{
		vm->arena[mdx(direct + i)].acb = (cmd->reg[0] >> ((3 - i) * 8)) & 0xFF;		
		//ft_printf("cmdREG|%d|\n", (cmd->reg[0] >> ((3 - i) * 8)) & 0xFF);
	}
}

int		vm_rdr2(t_vm *vm, t_cmd *cmd)
{
	int		pc;
	int		res;
	short	arg1;
	short	arg2;
	
	res = 0;
	pc = (cmd->idx - 1) + (0xFF & vm->arena[mdx(cmd->idx + 2)].acb);
	//ft_printf("PC %d %d\n", pc, vm->arena[mdx(cmd->idx + 2)].acb);
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
	res = pc + ((arg1 + arg2) % IDX_MOD);
	return (res);
}

int		vm_rir2(t_vm *vm, t_cmd *cmd)
{
	int		pc;
	int		res;
	int		arg1;
	short	arg2;
	
	res = 0;
	pc = (cmd->idx - 1) + (0xFF & vm->arena[mdx(cmd->idx + 2)].acb);
	arg1 = 0xFF & vm->arena[mdx(cmd->idx)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
	res = pc + (((arg1 % IDX_MOD) + arg2) % IDX_MOD);
	return (res);
}

int		vm_rrr2(t_vm *vm, t_cmd *cmd)
{
	int		pc;
	int		res;
	short	arg1;
	short	arg2;
	
	res = 0;
	pc = (cmd->idx - 1) + (0xFF & vm->arena[mdx(cmd->idx + 2)].acb);
	//ft_printf("PC %d %d\n", pc, vm->arena[mdx(cmd->idx + 2)].acb);
	arg1 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	arg1 <<= 8;
	arg1 += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	arg2 = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
	arg2 <<= 8;
	arg2 += 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
	res = pc + ((arg1 + arg2) % IDX_MOD);
	return (res);
}

void	vm_sti(t_vm *vm, t_cmd *cmd)
{
	int		cdg;
	int		direct;

	direct = 0;
	cdg = (0xFF & vm->arena[mdx(cmd->idx + 1)].acb);
	if (cdg == 104)		
		direct = vm_rdr2(vm, cmd);
	else if (cdg == 84)
		direct = vm_rdr2(vm, cmd);
	else if (cdg == 88)
		direct = vm_rdr2(vm, cmd);
	else if (cdg == 104)
		direct = vm_rdr2(vm, cmd);
	else if (cdg == 116)
		direct = vm_rir2(vm, cmd);
	load_res(vm, cmd, direct);
	vm->arena[mdx(cmd->idx)].rgb = cmd->rgb - 5;
	vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
}
