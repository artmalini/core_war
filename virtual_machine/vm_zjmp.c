
#include "vm.h"

void	vm_zjmp(t_vm *vm, t_cmd *cmd)
{
	//ft_printf("zjmp\n");
	short	place;

	if (cmd->carry)
	{
		place = 0xFF & vm->arena[mdx(cmd->idx + 1)].acb;
		place <<= 8;
		place += 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		//ft_printf("zjmp place %d", place);
		vm_next_step(vm, cmd, (place % IDX_MOD));
	}
	else
		vm_next_step(vm, cmd, 3);
}