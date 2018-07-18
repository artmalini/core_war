/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 14:32:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/03 14:32:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_print_error(t_error *e)
{
	perror(vm_str_error(e->id));
	exit(1);
}

char 		*vm_str_error(int error)
{
	if (error == ERROR_OPEN)
		return ("Failed to open");
	if (error == ERROR_READ)
		return ("Failed to read file");
	if (error == ERROR_CLOSE)
		return ("Failed to close file");
	if (error == ERROR_MAGIC)
		return ("Wrong Corewar Exec Magic");
	if (error == ERROR_NAME)
		return ("Incorrect Name Chars");
	if (error == ERROR_SIZE)
		return ("Player size too big");
	if (error == ERROR_PLAYER)
		return ("Too many players");
	if (error == ERROR_DUP)
		return ("Duplicate player number");
	if (error == ERROR_COMMENT)
		return ("Incorrect comment chars");
	if (error == ERROR_FILE)
		return ("Wrong file type. Usage: .cor");
	if (error == ERROR_SFILE)
		return ("The file size is too large.");
//	if (error == ERROR_ARG_PLAYER)
//		return ("No number after the -n. ");
//	if (error == ERROR_SFILE)
//		return ("The file size is too large.");
//	if (error == ERROR_SFILE)
//		return ("The file size is too large.");
	return ("Undefined\n");
}