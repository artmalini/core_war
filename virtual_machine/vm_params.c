/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:32:09 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/18 16:32:10 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				vm_isnumber(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
	}
	return (1);
}

int				vm_param_n(t_vm *vm, char **av, int *i, int ac)
{
	int		id;

	if (ac > (*i) + 1)
	{
		(*i)++;
		if (vm_isnumber(av[*i]))
		{
			id = ft_atoi(av[*i]);
			(*i)++;
			return (id);
		}
		else
		{
			ft_printf("No number after the -n. ");
			vm_exit(vm);	
		}
	}
	else
	{
		ft_printf("No champion after the number requested. ");
		vm_exit(vm);
		
	}
	return (vm->nbr_next);
}


void			vm_champs(t_vm *vm, char *arg)
{
	if ((vm->fd = open(arg, O_RDONLY)) >= 0 && vm->nbr_next <= 3)
	{
		vm_read_champ(vm, vm->nbr_next);
		close(vm->fd);
	}
	else if (vm->nbr_next >= 4)
	{
		ft_printf("Number of champion too high.\n");
		vm_exit(vm);
	}
		
}

void			vm_parse_params(t_vm *vm, int *i, char **av, int ac)
{
	if (((ft_strcmp(av[*i], "-n") == 0) || ft_strcmp(av[*i], "-dump") == 0))
	{
		if (ft_strcmp(av[*i], "-dump") == 0 && vm->dump_cycle == -1
				&& ac > *i + 2 && vm_isnumber(av[*i + 1]))
		{
			(*i)++;
			vm->dump_cycle = ft_atoi(av[*i]);
			(*i)++;
		}
		if (ft_strcmp(av[*i], "-n") == 0)
			vm->tab_champ[vm->nbr_next].id = vm_param_n(vm, av, i, ac);
	}
	if (!ft_strcmp(av[*i], "-d"))
	{
		vm->debug = 1;
		(*i)++;
	}
	if (!ft_strcmp(av[*i], "-v"))
	{
		vm->visual = 1;
		(*i)++;
	}
}

int				vm_get_param(char **av, t_vm *vm, int ac)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		vm_parse_params(vm, &i, av, ac);
		vm_champs(vm, av[i]);
	}
	if (vm->nbr_next == 0)
	{
		ft_printf("No .cor champion in the arena.\n");
		return (0);
	}
	return (1);
}

