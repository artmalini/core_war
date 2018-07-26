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

int 		ft_error_int(t_vm *vm, int id)
{
	if (!vm || !id)
		return (ERROR);
	if (id == ERROR_REG_CHAMP || id == ERROR_N_PARAM)
	{
		ft_printf("%s[%s]%s\n", RED, ft_str_cwa(id), RESET);
		vm_usage();
	}
	else if (id >= ON)
		ft_printf("%s[%s]%s\n", RED, ft_str_cwa(id), RESET);
	exit(EXIT_FAILURE);
	return (ERROR);
}

void 		ft_error(t_vm *vm, int id)
{
	if (!vm || !id)
		return ;
	if (id == ERROR_REG_CHAMP || id == ERROR_N_PARAM)
	{
		ft_printf("%s[%s]%s\n", RED, ft_str_cwa(id), RESET);
		vm_usage();
	}
	else if (id >= ON)
		ft_printf("%s[%s]%s\n", RED, ft_str_cwa(id), RESET);
	exit(EXIT_FAILURE);
}

char 		*ft_str_cwa(int error)
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
	return (ft_str_cwb(error));
}

char 		*ft_str_cwb(int error)
{
	if (error == ERROR_FT_ARG)
		return ("Invalid Function Input Arguments.");
	if (error == ERROR_CHAMP)
		return ("Invalid Number of Champion.");
	if (error == ERROR_NOT_CHAMP)
		return ("No [.cor] Champion in the arena.");
	if (error == ERROR_REG_CHAMP)
		return ("No Champion after the number requested.");
	if (error == ERROR_N_PARAM)
		return ("No Number after the [-n].");
	if (error == ERROR_BIG_CHAMP)
		return ("Champion too heavy.");
	if (error == ERROR_HEADER)
		return ("The Header of a Player is incorrect.");
	if (error == ERROR_MEMORY)
		return ("Don't free Memory for Malloc");
	//	if (error == ERROR_MEMORY)
//		return ("Don't free Memory for Malloc");
	//	if (error == ERROR_MEMORY)
//		return ("Don't free Memory for Malloc");
	return ("Undefined");
}
