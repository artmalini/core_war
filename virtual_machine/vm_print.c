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

// void		param_error(char *arg)
// {
// 	ft_putstr(arg);
// 	ft_putchar(' ');
// }

int			vm_usage(void)
{
	display_header();
	ft_putstr("Argument is EMPTY\n");
	//while (--argc)
	//	param_error(argv[i++]);
	//ft_putstr("is invalid!\n");
	ft_putstr("\033[33m ");
	//ft_putstr(argv[0]);
	ft_printf(" Usage :\n");
	ft_printf(" ./corewar [-a -dump nbr_cycles -d -v] "
						"[[-n number] champion1.cor] ...\n");
	ft_printf("\t\t\t\t\t -n number : You may write positive integer value instead this 'number'\n");
	ft_printf("\t\t-a\t\t: Prints output from 'aff' (Default is to hide it)\n");
	ft_printf("\t\t-dump nbr_cycles: Dumps memory after "
						"nbr_cycles then exits\n");
	ft_printf("\t\t-debug\t\t: Debug mode, show operations\n");
	ft_printf("\t\t-v\t\t: Visual mode\n");
	exit(1);
	return (0);
}