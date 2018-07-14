/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:23:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/04 14:23:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char 		*ft_str_asma(int id)
{
	if (id == ERROR_OPEN)
		return ("ERROR: Failed to OPEN file");
	if (id == ERROR_READ)
		return ("ERROR: Failed to READ file");
	if (id == ERROR_CLOSE)
		return ("ERROR: Failed to CLOSE file");
	if (id == ERROR_NAME)
		return ("ERROR: Incorrect NAME Chars");
	if (id == ERROR_A_NAME)
		return ("ERROR: To Many [.name] arguments");
	if (id == ERROR_L_NAME)
		return ("ERROR: Player's NAME to very long");
	if (id == ERROR_S_NAME)
		return ("ERROR: Player's NAME to very short");
	if (id == ERROR_CMT)
		return ("ERROR: Incorrect COMMENT Chars");
	if (id == ERROR_A_CMT)
		return ("ERROR: To Many [.comment] arguments");
	if (id == ERROR_L_CMT)
		return ("ERROR: Player's COMMENT length to long");
	if (id == ERROR_S_CMT)
		return ("ERROR: Player's COMMENT length to short");
	if (id == ERROR_SYNTAX)
		return ("ERROR: SYNTAX Error");
	return (ft_str_asmb(id));
}

int 		ft_error_int(t_core *file, int id)
{
	if (!file || !id)
		return (ERROR);
	if (id >= 1 && id <= 12)
		ft_printf("%s%s ---> %s[%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_FILE, ER_ROWS, RESET);
	if (id >= 13 && id <= 14)
		ft_printf("%s%s ---> %s[%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_LABEL, ER_ROWS, RESET);
	if (id >= 15 && id <= 17)
		ft_printf("%s%s ---> %s[%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_CMD, ER_ROWS, RESET);
	if (id >= 18 && id <= 22)
		ft_printf("%s%s ---> %s[%s][%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_CMD, ER_ARG, ER_ROWS, RESET);
	if (id >= 30)
		ft_printf("%s%s ---> %s[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_ROWS, RESET);
	free_struct_tcore(file);
	exit(EXIT_FAILURE);
	return (ERROR);
}

void 		ft_error(t_core *file, int id)
{
	if (!file || !id)
		return ;
	if (id >= 1 && id <= 12)
		ft_printf("%s%s ---> %s[%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_FILE, ER_ROWS, RESET);
	if (id >= 13 && id <= 14)
		ft_printf("%s%s ---> %s[%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_LABEL, ER_ROWS, RESET);
	if (id >= 15 && id <= 17)
		ft_printf("%s%s ---> %s[%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_CMD, ER_ROWS, RESET);
	if (id >= 18 && id <= 21)
		ft_printf("%s%s ---> %s[%s][%s]:[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_CMD, ER_ARG, ER_ROWS, RESET);
	if (id >= 30)
		ft_printf("%s%s ---> %s[%d]%s\n",
				  RED, ft_str_asma(id), BLUE, ER_ROWS, RESET);
	free_struct_tcore(file);
	exit(EXIT_FAILURE);
}

char 		*ft_str_asmb(int id)
{
	if (id == ERROR_ID_LABEL)
		return ("ERROR: More then one Identical LABELS");
	if (id == ERROR_LABEL)
		return ("ERROR: LABEL must be at least one character");
	if (id == ERROR_CMD)
		return ("ERROR: Wrong Name of COMMAND");
	if (id == ERROR_ARG)
		return ("ERROR: Wrong of command ARGUMENTS");
	if (id == ERROR_NBR_ARG)
		return ("ERROR: Wrong Number of command ARGUMENTS");

	if (id == ERROR_NAME_ARG)
		return ("ERROR: Incorrect ARGUMENT Chars");
	if (id == ERROR_T_DIR)
		return ("ERROR: Wrong Size of input T_DIR argument");
	if (id == ERROR_T_IND)
		return ("ERROR: Wrong Size of input T_IND argument");
	if (id == ERROR_ID_ARG)
		return ("ERROR: Wrong Identification of command ARGUMENTS");
	if (id == ERROR_TYPE_ARG)
		return ("ERROR: Invalid command argument Type");


	if (id == ERROR_LINE)
		return ("ERROR: At line (nbr)\n");
	if (id == ERROR_FT_ARG)
		return ("ERROR: Wrong input function arguments");
	if (id == ERROR_MEMORY)
		return ("ERROR: Don't have a MEMORY");
	return ("ERROR: LEXICAL Error");
}

//ft_printf("ERROR: %s at line %d\n", arg, file->rows);
//ft_printf("ERROR: wrong input arguments\n");
//ft_printf("ERROR: more then one identical labels\n");
//ft_printf("ERROR: syntax error\n");
//ft_printf("ERROR: Label must be at least one character\n");
