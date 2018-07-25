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

	i = 0;
	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	while (arg[i] && ft_strchr(SPACES_CHARS, arg[i]))
		i++;
	if (arg[i] == LABEL_CHAR)
	{
		i++;
		while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
			i++;
		if (arg[i] == '\0')
			return (OKAY);
	}
	return (ERROR);
}

int			check_arg_reg(t_core *file, t_cmd *c, const char *arg)
{
	int		len;
	int		hex;

	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (check_correct_end(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	if (check_digital_arg(file, c, arg))
		return (ft_error_int(file, ERROR_NAME_ARG));
	len = (int)ft_strlen(arg);
	if (len > 0 && ft_isdigit(*arg))
	{
		hex = ft_atoi(arg);
		if (hex > 0 && hex <= REG_NUMBER)
			return (OKAY);
	}
	return (ERROR);
}

int			check_arg_dir(t_core *file, t_cmd *c, const char *arg)
{
	int		i;
	int		nbr_arg;

	i = 0;
	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (arg[i] == LABEL_CHAR)
		return (check_arg_label(file, c, arg));
	if (check_correct_end(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	if (ft_isdigit(arg[i]) || (ft_strlen(arg + i) > 1 && arg[i] == '-' &&
			ft_isdigit(arg[i + 1])))
	{
		nbr_arg = ft_atoi(arg + i);
		if (SIZE(CMD) == ON)
		{
			if (nbr_arg >= INT16_MIN && nbr_arg <= INT16_MAX)
				return (OKAY);
			else
				return (ft_error_int(file, ERROR_T_DIR));
		}
		return (OKAY);
	}
	return (ERROR);
}

int			check_arg_ind(t_core *file, t_cmd *c, char *arg)
{
	int		i;
	int		len;

	i = 0;
	if (!file || !c || !arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (arg[i] == LABEL_CHAR)
		return (check_arg_label(file, c, arg));
	if (check_correct_end(file, c, arg) == ERROR)
		return (ft_error_int(file, ERROR_NAME_ARG));
	len = (int)ft_strlen(arg);
	while (i < len)
	{
		if (i == 0 && arg[i] == '-')
			i++;
		if (ft_strchr("01234567890", arg[i]))
			i++;
		else
			return (ft_error_int(file, ERROR_T_IND));
	}
	i = 0;
	if (ft_isdigit(arg[i]) || (ft_strlen(arg + i) > 1
								&& arg[i] == '-' && ft_isdigit(arg[i + 1])))
		return (OKAY);
	return (ERROR);
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
