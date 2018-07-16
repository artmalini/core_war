
#include "vm.h"

void	vm_zjmp(t_vm *vm, t_cmd *cmd)
{
	unsigned short	place;

	if (cmd->carry)
	{
		place = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
		place <<= 8;
		place += 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		vm_next_step(vm, cmd, ((short)place % IDX_MOD));
	}
	else
		vm_next_step(vm, cmd, 3);
}
