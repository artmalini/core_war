
#include "vm.h"

int		vm_v_cmd(int a, int b, int c)
{
	if (a < 0 || a >= REG_NUMBER ||	
		b < 0 || b >= REG_NUMBER ||
		c < 0 || c >= REG_NUMBER)
		return (0);
	return (1);
}

int		vm_sec(t_vm *vm, t_cmd *cmd, int *arg)
{
	unsigned int	one;
	unsigned short	two;

	if (arg[4] == 4)
	{
		one = 0xFF & vm->arena[mdx(cmd->idx + arg[3])].acb;
		one <<= 8;
		one = 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 1)].acb;
		one <<= 8;
		one = 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 2)].acb;
		one <<= 8;
		one = 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 3)].acb;
	}
	else if (arg[4] == 2)
	{
		two = 0xFF & vm->arena[mdx(cmd->idx + arg[3])].acb;
		two <<= 8;
		two = 0xFF & vm->arena[mdx(cmd->idx + arg[3] + 1)].acb;
		return ((short)two);
	}
	return ((int)one);
}

void	vm_rdr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_sec(vm, cmd, arg);

	if (cmd->reg[arg[1] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
		//printw("arg |%d|", cmd->carry);	
}




void	vm_and(t_vm *vm, t_cmd *cmd)
{
	int	arg[4];

	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 100)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 7)].acb;
		arg[2] = 0;
		arg[3] = 3;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[1] - 1))
			vm_rdr(vm, cmd, arg, 1);		
		//ft_printf("pos |%d| cmd->reg[arg[1] - 1]|%d|", vm_pos_curs(vm, cmd), cmd->reg[arg[1] - 2]);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
		//vm_next_step(vm, cmd, 8);
	}
}