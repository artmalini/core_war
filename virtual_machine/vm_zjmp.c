
#include "vm.h"

void	vm_zjmp(t_vm *vm, t_cmd *cmd)
{
	//ft_printf("zjmp\n");
	vm_next_step(vm, cmd, -5);
}