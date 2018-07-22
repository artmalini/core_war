/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 14:36:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/03 14:36:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_header(void)
{
	ft_putstr("\033[31m");
	ft_putstr("    ><<             ><<<<<<<    ><<<<<<<<\n");
	ft_putstr(" ><<   ><<          ><<    ><<  ><<      \n");
	ft_putstr("><<          ><<    ><<    ><<  ><<      \n");
	ft_putstr("><<        ><<  ><< >< ><<      ><<<<<<  \n");
	ft_putstr("><<       ><<    ><<><<  ><<    ><<      \n");
	ft_putstr(" ><<   ><< ><<  ><< ><<    ><<  ><<      \n");
	ft_putstr("   ><<<<     ><<    ><<      ><<><<<<<<<<\n\n");
}

void		param_error(char *arg)
{
	ft_putstr(arg);
	ft_putchar(' ');
}

int			vm_usage(int argc, char **argv)
{
	int		i;

	i = 1;
	display_header();
	ft_putstr("ERROR: Arguments ");
	while (--argc)
		param_error(argv[i++]);
	ft_putstr("is invalid!\n");
	ft_putstr("\033[33m ");
	ft_putstr(argv[0]);
	ft_printf(" usage : ./corewar [-dump nbr_cycles]"
					  "[[-n number] champion1.cor] ...\n");
	exit(1);
	return (0);
}