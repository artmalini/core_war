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

int 		ft_error_int(t_core *file, int id)
{
	if (!file || !id)
		return (ERROR);
	file->error->id = id;
	if (id == ERROR_OPEN || id == ERROR_READ || id == ERROR_CLOSE ||
		id == ERROR_INPUT)
		ft_printf("%s%s ---> [%s]%s\n", RED, ft_str_asma(file->error->id),
				  file->error->arg, RESET);
	else if (id == ERROR_ID_ARG || id == ERROR_T_IND || id == ERROR_T_DIR ||
			 id == ERROR_TYPE_ARG)
		ft_printf("%s%s ---> [%s]%s\n", RED, ft_str_asma(file->error->id),
				  file->error->current_arg, RESET);
	else if (id > 0)
		ft_printf("%s%s ---> [%s]%s\n", RED, ft_str_asma(file->error->id),
				  "VOID", RESET);
	else if (file->error->id)
		ft_printf("%s%s%s\n", RED, ft_str_asma(file->error->id), RESET);
	free_struct_tcore(file);
	exit(ERROR);
	return (ERROR);
}

void 		ft_error(t_core *file, int id)
{
	if (!file || !id)
		return ;
	file->error->id = id;
	if (id == ERROR_OPEN || id == ERROR_READ || id == ERROR_CLOSE ||
		id == ERROR_INPUT)
		ft_printf("%s%s ---> [%s]%s\n", RED, ft_str_asma(file->error->id),
				  file->error->arg, RESET);
	else if (id == ERROR_ID_ARG || id == ERROR_T_IND || id == ERROR_T_DIR ||
			 id == ERROR_TYPE_ARG)
		ft_printf("%s%s ---> [%s]%s\n", RED, ft_str_asma(file->error->id),
				  file->error->current_arg, RESET);
	else if (id > 0)
		ft_printf("%s%s ---> [%s]%s\n", RED, ft_str_asma(file->error->id),
				  "VOID", RESET);
	else if (file->error->id)
		ft_printf("%s%s%s\n", RED, ft_str_asma(file->error->id), RESET);
	free_struct_tcore(file);
	exit(ERROR);
}

char 		*ft_str_asma(int id)
{
	if (id == ERROR_OPEN)
		return ("ERROR: Failed to open file");
	if (id == ERROR_READ)
		return ("ERROR: Failed to read file");
	if (id == ERROR_CLOSE)
		return ("ERROR: Failed to close file");
	if (id == ERROR_INPUT)
		return ("ERROR: Wrong input");
	if (id == ERROR_NAME)
		return ("ERROR: Wrong Name Chars");
	if (id == ERROR_L_NAME)
		return ("ERROR: Name to long");
	if (id == ERROR_S_NAME)
		return ("ERROR: Name to short");
	if (id == ERROR_CMT)
		return ("ERROR: Incorrect Comment Chars");
	if (id == ERROR_L_CMT)
		return ("ERROR: Comment length to long");
	if (id == ERROR_S_CMT)
		return ("ERROR: Comment length to short");
	if (id == ERROR_SYNTAX)
		return ("ERROR: Syntax error");
	return (ft_str_asmb(id));
}

char 		*ft_str_asmb(int id)
{

	if (id == ERROR_LINE)
		return ("ERROR: At line (nbr)\n");
	if (id == ERROR_A_NAME)
		return ("ERROR: To many .name arguments");
	if (id == ERROR_A_CMT)
		return ("ERROR: To many .comment arguments");
	if (id == ERROR_ID_LABEL)
		return ("ERROR: More then one identical labels");
	if (id == ERROR_LABEL)
		return ("ERROR: Label must be at least one character");
	if (id == ERROR_CMD)
		return ("ERROR: Wrong command name");
	if (id == ERROR_MEMORY)
		return ("ERROR: Don't have a Memory");
	if (id == ERROR_FT_ARG)
		return ("ERROR: Wrong input function arguments");
	if (id == ERROR_ARG)
		return ("ERROR: Wrong input arguments of command");
	if (id == ERROR_T_DIR)
		return ("ERROR: Wrong size of input T_DIR argument");
	if (id == ERROR_T_IND)
		return ("ERROR: Wrong size of input T_IND argument");
	if (id == ERROR_NBR_ARG)
		return ("ERROR: Wrong count arguments of command");
	if (id == ERROR_ID_ARG)
		return ("ERROR: Identification of the command argument");
	if (id == ERROR_TYPE_ARG)
		return ("ERROR: Invalid command argument Type");
	return ("ERROR: Syntax error");
}

//	if (c == 0)
//	ft_printf("ERROR: %s at line %d\n", arg, file->rows);
//	else if (c == 1)
//		ft_printf("ERROR: wrong input arguments\n");
//	else if (c == 2)
//		ft_printf("ERROR: wrong input\n");
//	else if (c == 3)
//		ft_printf("ERROR: %s wrong file name\n", arg);
//	else if (c == 4)
//		ft_printf("ERROR: Open file %s error\n", arg);
//	else if (c == 5)
//		ft_printf("ERROR: %s wrong_syntax\n", arg);
//	else if (c == 6)
//		ft_printf("ERROR: %s to many .name arguments\n", arg);
//	else if (c == 7)
//		ft_printf("ERROR: %s to many .comment arguments\n", arg);
//	else if (c == 8)
//		ft_printf("ERROR: %s Name to long\n", arg);
//	else if (c == 9)
//		ft_printf("ERROR: %s Name to short\n", arg);
//	else if (c == 10)
//		ft_printf("ERROR: %s Comment length to long\n", arg);
//	else if (c == 11)
//		ft_printf("ERROR: %s Comment length to short\n", arg);

//void	error_cor(t_core *file, int nbr_char)
//{
//	if (nbr_char == 0)
//		ft_printf("ERROR: more then one identical labels\n");
//	else if (nbr_char == 1)
//		ft_printf("ERROR: syntax error\n");
//	else if (nbr_char == 2)
//		ft_printf("ERROR: Label must be at least one character\n");
//	free_struct_tcore(file);
//	exit(ERROR);
//}