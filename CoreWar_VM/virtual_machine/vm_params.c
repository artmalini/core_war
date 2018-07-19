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

static int		vm_param_n(t_vm *vm, char **av, int *i, int ac)
{
	int			id;

	if (ac > (*i) + 1)
	{
		(*i)++;
		if (ft_isnumber(av[*i]))
		{
			id = ft_atoi(av[*i]);
			(*i)++;
			return (id);
		}
		else
			return (ft_error_int(vm, ERROR_N_PARAM));
	}
	else
		return (ft_error_int(vm, ERROR_REG_CHAMP));
//	return (vm->nbr_next);
}

int				vm_get_param(t_vm *vm, char **av, int ac)
{
	int			i;

	i = 0;
	while (++i < ac)
	{
		if (((ft_strcmp(av[i], "-n") == 0) || ft_strcmp(av[i], "-dump") == 0))
		{
			if (ft_strcmp(av[i], "-dump") == 0 && vm->dump_cycle == -1
				&& ac > i + 2 && ft_isnumber(av[i + 1]))
			{
				i++;
				vm->dump_cycle = ft_atoi(av[i]);
				i++;
			}
			if (ft_strcmp(av[i], "-n") == 0)
				vm->tab_champ[vm->nbr_next].id = vm_param_n(vm, av, &i, ac);
		}
		if (!ft_strcmp(av[i], "-d"))
		{
			vm->debug = 1;
			i++;
		}
		vm_parse_champs(vm, av[i]);
	}
	if (!vm->current_player)
		return (ft_error_int(vm, ERROR_NOT_CHAMP));
	vm->total_players = vm->current_player;
	vm->current_player = OFF;
	return (OKAY);
}
