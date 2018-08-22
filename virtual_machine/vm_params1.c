
#include "vm.h"

int			vm_isnumber(char *str)
{
	int		i;

	i = -1;
	if (str[0] == '-')
	{
		i++;
		if (str[1] == '\0')
			return (0);
	}
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
	}
	return (1);
}

int			vm_param_n(t_vm *vm, char **av, int *i, int ac)
{
	int		id;

	if (ac > (*i) + 1)
	{
		(*i)++;
		if (av[*i] && vm_isnumber(av[*i]))
		{
			id = ft_atoi(av[*i]);
			if (id <= 0)
				vm_err_exit(vm, ERR_NBR_INV);
			(*i)++;
			return (id);
		}
		else
			vm_err_exit(vm, ERR_NO_NBR);
	}
	else
		vm_err_exit(vm, ERR_NO_CHMP);
	return (vm->nbr_next);
}

void		vm_champs(t_vm *vm, char *arg)
{
	if ((vm->fd = open(arg, O_RDONLY)) >= 0 && vm->nbr_next <= 3)
	{
		vm_read_champ(vm, vm->nbr_next);
		close(vm->fd);
	}
	else if (vm->nbr_next >= 4)
		vm_err_exit(vm, ERR_NBR_CHMP);
		
}
