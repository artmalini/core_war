/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:33:31 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/18 16:33:32 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					vm_len_magic(unsigned char *str, int nbr)
{
	unsigned int	nb;
	unsigned int	val;

	nb = 0;
	while (nbr > 0)
	{
		nb <<= 8;
		val = (unsigned int)(*str);
		nb = nb | val;
		str++;
		nbr--;
	}
	return (nb);
}

static void			check_magic(const char *str)
{
	unsigned int	magic;

	magic = vm_len_magic((unsigned char*)str, 4);
	if (magic != COREWAR_EXEC_MAGIC)
	{
		display_header();
		ft_printf("The header of a player is incorrect.\n");
		exit(1);
	}
}

static void			check_size(t_vm *vm, int size, int nb_player, char *str)
{
	unsigned int	size_bit;
	int				real_size;

	real_size = size - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	if (real_size > CHAMP_MAX_SIZE)
	{
		display_header();
		ft_printf("Champion too heavy.\n");
		exit(1);
	}
	size_bit = str[0];
	size_bit <<= 8;
	size_bit |= str[1];
	size_bit <<= 8;
	size_bit |= str[2];
	size_bit <<= 8;
	size_bit |= str[3];
	vm->tab_champ[nb_player].weight = real_size;
}

static void			cpy_prog(t_vm *vm, char *prog, int num_player)
{
	int				index;

	if (!(vm->tab_champ[num_player].prog = malloc(sizeof(unsigned char) * \
	vm->tab_champ[num_player].weight)))
		exit(1);
	index = 0;
	while (index < vm->tab_champ[num_player].weight)
	{
		vm->tab_champ[num_player].prog[index] = prog[index];
		index++;
	}
}

void				vm_read_champ(t_vm *vm, int nbr_player, int size)
{
	char			str[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	int				ret;

	size = lseek(vm->fd, 0, SEEK_END);
	lseek(vm->fd, 0, SEEK_SET);
	ft_bzero(str, 4);
	read(vm->fd, str, 4);
	check_magic(str);
	read(vm->fd, str, PROG_NAME_LENGTH);
	vm->tab_champ[nbr_player].name = ft_strdup(str);
	read(vm->fd, str, 4);
	read(vm->fd, str, 4);
	check_size(vm, size, nbr_player, str);
	read(vm->fd, comment, COMMENT_LENGTH);
	ft_strcpy(vm->tab_champ[nbr_player].comment, comment);
	ft_bzero(comment, COMMENT_LENGTH);
	read(vm->fd, str, 4);
	if (!(ret = read(vm->fd, comment, vm->tab_champ[nbr_player].weight)))
		return ;
	cpy_prog(vm, comment, nbr_player);
	if (vm->tab_champ[nbr_player].id == -1)
		vm->tab_champ[nbr_player].id = vm->nbr_next + 1;
	vm->nbr_next++;
}
