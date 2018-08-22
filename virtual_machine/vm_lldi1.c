
#include "vm.h"

void	vm_lldi_next(t_vm *vm, t_cmd *cmd, int x, int hex)
{
	if (hex == 228 || hex == 164)
		lldi_idr_ddr(vm, cmd, hex);
	else if (hex == 212 || hex == 148 || hex == 100)
	{
		lldi_irr_drr(vm, cmd, hex);
		vm_lldi_rdr(vm, cmd, hex);
	}
	else
		vm_next_step(vm, cmd, vm_len_step(vm, cmd, x));
}
