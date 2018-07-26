/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:33:31 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/18 16:33:32 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				vm_check_magic(t_vm *vm, const char *str)
{
	int				magic[4];

	magic[0] = str[3];
	magic[1] = str[2];
	magic[2] = str[1];
	magic[3] = str[0];
	if (magic[0] != -13 || magic[1] != -125 ||magic[2] != -22 || magic[3] != 0)
		return (ft_error(vm, ERROR_HEADER));
}

void				vm_check_size(t_vm *vm, const char *str)
{
	unsigned int	size_bit;
	size_t			real_size;
	size_t 			file_weight;

	file_weight = vm->tab_champ[PLAYER].file_weight;
	real_size = file_weight - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	if (real_size > CHAMP_MAX_SIZE)
		return (ft_error(vm, ERROR_BIG_CHAMP));
	size_bit = (unsigned int)str[0];
	size_bit <<= 8;
	size_bit |= str[1];
	size_bit <<= 8;
	size_bit |= str[2];
	size_bit <<= 8;
	size_bit |= str[3];
	WEIGHT(PLAYER) = real_size;
}
