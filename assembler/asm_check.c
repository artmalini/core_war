/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:46:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/14 17:46:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int 		check_digital_arg(t_core *file, t_cmd *c, const char *arg)
{
	int 	i;
	int 	len;

	i = 0;
	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	len = (int)ft_strlen(arg);
//	while (ft_isdigit(arg[i]))
//		i++;
//	while (!ft_strchr(SPACES_CHARS, arg[i]))
//		i++;
//	if (len == i)
		return (OKAY);
//	return (ERROR);
}

int 		check_comma_args(t_core *file, t_cmd *c, const char *args)
{

	int 	i;
	int		len;
	int 	comma;

	i = 0;
	comma = 0;
	if (!file || !c || !args)
		return (ft_error_int(file, ERROR_FT_ARG));
	len = (int)ft_strlen(args);
	while (len > i)
	{
		if (ft_strchr(",", args[i++]))
			comma++;
	}
	if ((comma + 1) == c->nbr_args)
		return (OKAY);
	return (ERROR);
}

int			check_arg_of_cmd(t_core *file, t_cmd *c)
{
	int 	nbr;
	int 	arg;

	nbr = 0;
	if (!file || !c)
		return (ft_error_int(file, ERROR_FT_ARG));
	while (c->nbr_args > nbr)
	{
		file->error->current_arg = c->args[nbr];
		if (c->args[nbr][0] == REGISTER_CHAR)
			arg = T_REG;
		else if (c->args[nbr][0] == DIRECT_CHAR)
			arg = T_DIR;
		else arg = T_IND;
		if (!(TYPE_ARG(nbr) & arg))
			return (ERROR);
		nbr++;
	}
	return (OKAY);
}

int 		check_correct_end(t_core *file, t_cmd *c, const char *str_arg)
{
	int 	i;
	int 	len;

	i = 0;
	if (!file || !c || !str_arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	len = (int)ft_strlen(str_arg);
	while (str_arg[i] && len > i && !ft_strchr(SPACES_CHARS, str_arg[i]))
		i++;
	while (str_arg[i] && len > i && ft_strchr(SPACES_CHARS, str_arg[i]))
		i++;
	if (len == i)
		return (OKAY);
	return (ERROR);
}