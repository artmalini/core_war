
#include "vm.h"

void	vm_dump_arena(t_vm *vm)
{
	int	i;
	int	mem;

	mem = 64;
	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", 0xFF & vm->arena[i].acb);
		if ((i + 1) % 64 == 0)
		{ 
			if (i + 1 < MEM_SIZE)
			{
				ft_printf("\n");
				ft_printf("%#06x : ", mem);
			}
			mem += 64;
		}
		i++;
	}
	ft_printf("\n");
}
