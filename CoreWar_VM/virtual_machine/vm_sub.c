
#include "vm.h"

void	vm_sub(t_vm *vm, t_cmd *cmd)
{
	int		a;
	int		b;
	int		c;

	a = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	b = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	c = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm_v_cmd(a - 1, b - 1, c - 1))
	{
		cmd->reg[c - 1] = cmd->reg[a - 1] - cmd->reg[b - 1];
		cmd->carry = (cmd->reg[c - 1] == 0) ? 1 : 0;
		vm_next_step(vm, cmd, 5);
	}
	else
		vm_next_step(vm, cmd, 5);
}
