
#include "vm.h"

void	vm_live(t_vm *vm, t_cmd *cmd)
{
	//ft_printf("TTT|%d|", 5);
	//refresh();
	vm_next_step(vm, cmd, 5);
}
