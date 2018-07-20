/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 20:38:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/19 20:38:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		vm_cpy_prog(t_vm *vm, const char *prog)
{
	size_t		index;

	index = 0;
	if (!(PROG(PLAYER) = malloc(sizeof(unsigned char) * WEIGHT(PLAYER))))
		return (ft_error(vm, ERROR_MEMORY));
	while (index < WEIGHT(PLAYER))
	{
		(PROG(PLAYER))[index] = prog[index];
		index++;
	}
}

static void		vm_read_champ(t_vm *vm, char *name)
{
	if (!vm || !name)
		return (ft_error(vm, ERROR_FT_ARG));
	ft_bzero(name, PROG_NAME_LENGTH);
	if (read(vm->fd, name, 4) == ERROR)
		return (ft_error(vm, ERROR_READ));
	vm_check_magic(vm, name);
	if (read(vm->fd, name, PROG_NAME_LENGTH) == ERROR)
		return (ft_error(vm, ERROR_READ));
	NAME(PLAYER) = ft_strdup(name);
	ft_bzero(name, PROG_NAME_LENGTH);
	if (read(vm->fd, name, 4) == ERROR)
		return (ft_error(vm, ERROR_READ));
	if (read(vm->fd, name, 4) == ERROR)
		return (ft_error(vm, ERROR_READ));
	vm_check_size(vm, name);
}

static void		vm_read_main(t_vm *vm, char *name, char *comment)
{
	if (!vm || !name || !comment)
		return (ft_error(vm, ERROR_FT_ARG));
	lseek(vm->fd, 0, SEEK_SET);
	vm_read_champ(vm, name);
	ft_bzero(comment, COMMENT_LENGTH);
	if (read(vm->fd, comment, COMMENT_LENGTH) == ERROR)
		return (ft_error(vm, ERROR_READ));
	ft_strcpy(COMMENT(PLAYER), comment);
	ft_bzero(comment, COMMENT_LENGTH);
	if (read(vm->fd, name, 4) == ERROR)
		return (ft_error(vm, ERROR_READ));
	if ((read(vm->fd, comment, WEIGHT(PLAYER))) == ERROR)
		return (ft_error(vm, ERROR_READ));
	else
		vm_cpy_prog(vm, comment);
	if (ID(PLAYER) == OFF)
		ID(PLAYER) = (int)PLAYER + 1;
	vm->nbr_next++;
	if (vm->debug == ON)
		vm_print_debug_champ(vm);
}

void		vm_parse_champs(t_vm *vm, char *arg)
{
	size_t 	file_weight;
	char	name[PROG_NAME_LENGTH];
	char	comment[COMMENT_LENGTH];

	if (!vm || !arg)
		return (ft_error(vm, ERROR_FT_ARG));
	if (++vm->current_player > MAX_PLAYERS)
		return (ft_error(vm, ERROR_CHAMP));
	if (!(vm->fd = open(arg, O_RDONLY)))
		return (ft_error(vm, ERROR_OPEN));
	file_weight = (size_t)lseek(vm->fd, 0, SEEK_END);
	vm->tab_champ[PLAYER].file_weight = file_weight;
	ft_bzero(name, PROG_NAME_LENGTH);
	ft_bzero(comment, COMMENT_LENGTH);
	vm_read_main(vm, name, comment);
	if (close(vm->fd))
		return (ft_error(vm, ERROR_CLOSE));
}
