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

int				vm_param_n(t_vm *vm, char **av, int *i, int ac)
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


void			vm_champs(t_vm *vm, char *arg)
{
	if ((vm->fd = open(arg, O_RDONLY)) >= 0 && vm->nbr_next <= 3)
	{
		vm_read_champ(vm, vm->nbr_next);
		close(vm->fd);
	}
	else if (vm->nbr_next >= 4)
		vm_err_exit(vm, ERR_NBR_CHMP);
		
}

void			vm_parse_params1(t_vm *vm, int *i, char **av)
{
	if (av[*i] && !ft_strcmp(av[*i], "-a"))
	{
		vm->aff = 1;
		(*i)++;
	}
	if (av[*i] && !ft_strcmp(av[*i], "-v"))
	{
		vm->visual = 1;
		vm->on = 1;
		(*i)++;
	}
	if (av[*i] && !ft_strcmp(av[*i], "-lives") && vm->on == 0)
	{
		vm->show_live = 1;
		vm->on = 1;
		(*i)++;
	}
}

void			vm_parse_params(t_vm *vm, int *i, char **av, int ac)
{
	vm_parse_params1(vm, i, av);
	if (av[*i] && ((ft_strcmp(av[*i], "-n") == 0) ||
		ft_strcmp(av[*i], "-dump") == 0))
	{
		if (av[*i] && ft_strcmp(av[*i], "-dump") == 0 && vm->dump_cycle == -1
				&& ac > *i + 2 && vm_isnumber(av[*i + 1]) && vm->on == 0)
		{
			(*i)++;
			vm->dump_cycle = ft_atoi(av[*i]);
			if (vm->dump_cycle == 0)
				vm->dump_cycle = 1;
			(*i)++;
		}
		if (av[*i] && ft_strcmp(av[*i], "-n") == 0)
			vm->tab_champ[vm->nbr_next].id = vm_param_n(vm, av, i, ac);
	}
	if (av[*i] && !ft_strcmp(av[*i], "-debug")
		&& vm->on == 0 && vm->aff == 0)
	{
		vm->debug = 1;
		(*i)++;
	}
}

int				vm_c_champ(char *str)
{
	int		j;
	int		dot;

	j = -1;
	dot = 0;
	while (str && str[++j])
	{
		if ((str[j] >= 9 && str[j] <= 13) || str[j] == 32)		
			return (0);
		if (str[j] == '.')
        {
			dot++;
		    break ;
        }
	}
	if (dot != 1)
		return (0);
	if (str)
    {
        if (!ft_strcmp(str + j, ".cor"))
            return (1);
        else
            return (0);
    }
    return (0);
}

void			vm_simpl_err(char *str)
{
	display_header();
	if (!str)
		ft_printf("Error: No .cor champion in the arena.\n");
	else
		ft_printf("Error: Can't read source file %s\n", str);
}

int				vm_get_param(char **av, t_vm *vm, int ac)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		vm_parse_params(vm, &i, av, ac);		
		if (av[i] != NULL && av[i][0] == '-')
		{
			vm_simpl_err(av[i]);
			return (0);	
		}
		if(!vm_c_champ(av[i]))
		{
			vm_simpl_err(av[i]);
			return (0);
		}
		vm_champs(vm, av[i]);
	}
	if (vm->nbr_next == 0)
	{
		vm_simpl_err(NULL);
		return (0);
	}
	return (1);
}

