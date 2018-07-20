/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:59:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/19 16:59:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_print_debug_champ(t_vm *vm)
{
	if (PLAYER == 0)
		ft_printf("Introducing contestants...\n");
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			  (PLAYER + 1), WEIGHT(PLAYER), NAME(PLAYER), COMMENT(PLAYER));
}