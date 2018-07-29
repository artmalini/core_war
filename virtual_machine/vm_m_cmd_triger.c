
#include "vm.h"

void	vm_cmd_triger2(t_vm *vm, t_cmd *cmd, int hex)
{
	if (hex == 12)
		vm_fork(vm, &cmd);
	else if (hex == 13)
		vm_lld(vm, cmd);
	else if (hex == 14)
		vm_lldi(vm, cmd);
	else if (hex == 15)
		vm_lfork(vm, &cmd);
	else if (hex == 16)
		vm_aff(vm, cmd);
	else
		return ;
}

void	vm_cmd_triger(t_vm *vm, t_cmd *cmd, int hex)
{
	if (hex == 1)
		vm_live(vm, cmd);
	else if (hex == 2)
		vm_ld(vm, cmd);
	else if (hex == 3)
		vm_st(vm, cmd);
	else if (hex == 4)
		vm_add(vm, cmd);
	else if (hex == 5)
		vm_sub(vm, cmd);
	else if (hex == 6)
		vm_and(vm, cmd);
	else if (hex == 7)
		vm_or(vm, cmd);
	else if (hex == 8)
		vm_xor(vm, cmd);
	else if (hex == 9)
		vm_zjmp(vm, cmd);
	else if (hex == 10)
		vm_ldi(vm, cmd);
	else if (hex == 11)
		vm_sti(vm, cmd);
	else
		vm_cmd_triger2(vm, cmd, hex);
}
