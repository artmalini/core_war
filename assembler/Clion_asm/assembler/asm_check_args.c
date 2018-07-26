/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:30:41 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/08 15:30:43 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_arg_label(t_core *file, t_cmd *c, const char *arg)
{
	int		i;
	int 	end;

	i = 0;
	if (!file || !c || !arg || !(end = (int)ft_strlen(arg)))
		return (ft_error_int(file, ERROR_FT_ARG));
	while (end >= 1 && ft_strchr(SPACES_CHARS, arg[end - 1]))
		end--;
	if (arg[i] == LABEL_CHAR)
		i++;
	while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
		i++;
	if (i == end)
		return (OKAY);
	return (ERROR);
}

int			check_arg_reg(t_core *file, t_cmd *c, const char *arg)
{
	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (check_correct_end(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	if (check_digital_arg(file, c, arg))
		return (ft_error_int(file, ERROR_NAME_ARG));
	if (ft_atoi(arg) > 0 && ft_atoi(arg) <= REG_NUMBER)
		return (OKAY);
	return (ERROR);
}

int			check_arg_dir(t_core *file, t_cmd *c, const char *arg)
{
	int		i;

	i = 0;
	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (arg[i] == LABEL_CHAR)
		return (check_arg_label(file, c, arg));
	if (check_correct_end(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	if (check_digital_arg(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	if (SIZE(CMD) == ON)
	{
		if (ft_atoi(arg) >= INT16_MIN && ft_atoi(arg) <= INT16_MAX)
			return (OKAY);
		else
			return (ft_error_int(file, ERROR_T_DIR));
	}
	return (OKAY);
}

int			check_arg_ind(t_core *file, t_cmd *c, char *arg)
{
	int		i;

	i = 0;
	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (arg[i] == LABEL_CHAR)
		return (check_arg_label(file, c, arg));
	if (check_correct_end(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	if (check_digital_arg(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	return (OKAY);
}

int			check_args_main(t_core *file, t_cmd *c, char **args)
{
	int		i;
	int		nbr;
	int		status;

	nbr = 0;
	while (c->nbr_args > nbr && args[nbr])
	{
		i = 0;
		while (args[nbr][i] && ft_strchr(SPACES_CHARS, args[nbr][i]))
			i++;
		file->error->current_arg = &(args[nbr][i]);
		if (args[nbr][i] && args[nbr][i] == REGISTER_CHAR)
			status = check_arg_reg(file, c, (args[nbr] + i + 1));
		else if (args[nbr][i] && args[nbr][i] == DIRECT_CHAR)
			status = check_arg_dir(file, c, (args[nbr] + i + 1));
		else if (ft_isdigit(args[nbr][i]) || args[nbr][i] == LABEL_CHAR ||
				args[nbr][i] == '-')
			status = check_arg_ind(file, c, (args[nbr] + i));
		else
			return (ft_error_int(file, ERROR_ID_ARG));
		if (status != OKAY)
			return (ERROR);
		nbr++;
	}
	return (OKAY);
}
