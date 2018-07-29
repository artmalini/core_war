
#include "vm.h"

void		free_vm(t_vm *vm)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;
	int		i;

	i = -1;
	if (vm)
	{
		while (++i < vm->nbr_next)
		{
			free(vm->tab_champ[i].name);
			free(vm->tab_champ[i].prog);
		}
		if (vm->cmd)
		{
			tmp = vm->cmd;
			while (tmp)
			{
				tmp1 = tmp;
				tmp = tmp->next;
				free(tmp1);
			}
		}
		free(vm);
	}
}

void		vm_exit(t_vm *vm)
{
	if (vm)
		free(vm);
	exit(1);
}
