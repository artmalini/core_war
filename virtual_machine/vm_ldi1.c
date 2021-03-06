/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ldi1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:02:12 by amakhiny          #+#    #+#             */
/*   Updated: 2018/08/23 12:02:23 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_ldi_next(t_vm *vm, t_cmd *cmd, int x, int hex)
{
	if (hex == 228 || hex == 164)
		vm_ldi_idr_ddr(vm, cmd, hex);
	else if (hex == 212 || hex == 148 || hex == 100)
	{
		vm_ldi_irr_drr(vm, cmd, hex);
		vm_ldi_rdr(vm, cmd, hex);
	}
	else
		vm_next_step(vm, cmd, vm_len_step(vm, cmd, x));
}
