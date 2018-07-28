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
	ft_putstr("ERROR: Argument ");
	while (--argc)
		param_error(argv[i++]);
	ft_putstr("is invalid!\n");
	ft_putstr("\033[33m ");
	ft_putstr(argv[0]);
	ft_printf(" usage :\n");
	ft_printf(" ./corewar [-dump nbr_cycles -d -v] "
						"[[-n number] champion1.cor] ...\n");
	ft_printf("\t    -dump nbr_cycles	: Dumps memory after "
						"nbr_cycles then exits\n");
	ft_printf("\t    -d\t\t	: Debug mode, show operations\n");
	ft_printf("\t    -v\t\t	: Visual mode\n");
	exit(1);
	return (0);
}