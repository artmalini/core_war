
#include "vm.h"

/*
** 80  == (T_REG, T_REG)
** 112 == (T_REG, T_IND)
*/

void	vm_st_rr(t_vm *vm, t_cmd *cmd, int reg1, int reg2)
{
	if (vm->debug)
		ft_printf("|P\t%d| st |r%d| |%d|\n", cmd->nbr_process, reg1, reg2);
	cmd->reg[reg2 - 1] = cmd->reg[reg1 - 1];
	vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
}

void	vm_st_ri(t_vm *vm, t_cmd *cmd, int reg1)
{
	int		i;
	short	two;
	int		two_val;

	i = -1;
	two = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	two_val = two % IDX_MOD;
	//printf("%d", two % IDX_MOD);
	while (++i <= 3)
	{
		vm->arena[mdx(cmd->idx + two_val + i)].acb =
			((cmd->reg[reg1 - 1]) >> ((3 - i) * 8)) & 0xFF;
		vm->arena[mdx(cmd->idx + two_val + i)].rgb = cmd->rgb - 4;
		vm->arena[mdx(cmd->idx + two_val + i)].asc_rgb = cmd->rgb - 4;
		//vm->arena[mdx(cmd->idx + (two % IDX_MOD) + i)].bold = 50;
	}
	if (vm->debug)
		ft_printf("|P\t%d| st |r%d| value |%d|\n", cmd->nbr_process, reg1, two_val);
	//vm->arena[mdx(cmd->idx + (two % IDX_MOD) + i)].rgb = cmd->rgb - 5;
	//ft_printf("st_ri|%d| ", (short)two % IDX_MOD);
	vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
}

void	vm_st(t_vm *vm, t_cmd *cmd)
{
	int	reg1;
	int	reg2;
	//ft_printf("vm_st");
	reg1 = vm->arena[mdx(cmd->idx + 2)].acb;	
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 80)
	{		
		reg2 = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
		if (vm_v_cmd(reg1 - 1, reg2 - 1, reg2 - 1))
			vm_st_rr(vm, cmd, reg1, reg2);
	}
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 112)
	{
		//ft_printf("tt");
		if (vm_v_cmd(reg1 - 1, reg1 - 1, reg1 - 1))
			vm_st_ri(vm, cmd, reg1);
	}
}