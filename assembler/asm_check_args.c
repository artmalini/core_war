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

int			check_arg_label(t_core *file, t_cmd *c, char *str_arg)
{
	int		i;

	i = 0;
	if (!file || !c || !str_arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	while (str_arg[i] && ft_strchr(SPACES_CHARS, str_arg[i]))
		i++;
	if (str_arg[i] == DIRECT_CHAR)
		i++;
	if (str_arg[i] == LABEL_CHAR)
	{
		i++;
		while (str_arg[i] && ft_strchr(LABEL_CHARS, str_arg[i]))
			i++;
		if (str_arg[i] == '\0')
			return (OKAY);
	}
	return (ERROR);
}

int			check_arg_reg(t_core *file, t_cmd *c, char *str_arg)
{
    int		i;
	int 	len;
    int		hex;

    i = 0;
    if (!file || !c || !str_arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	len = (int)ft_strlen(str_arg);
    if (len > 0 && len < 3 && ft_isdigit(str_arg[i]))
    {
		hex = ft_atoi(str_arg);
        if (hex > 0 && hex <= REG_NUMBER)
            return (OKAY);
    }
    return (ERROR);
}

int			check_arg_dir(t_core *file, t_cmd *c, char *str_arg)
{
    int		i;
    int		arg;

    i = 0;
    if (!file || !c || !str_arg)
		return (ft_error_int(file, ERROR_FT_ARG));
    if (str_arg[i] == LABEL_CHAR)
        return (check_arg_label(file, c, str_arg));
    else if (ft_isdigit(str_arg[i]) || (ft_strlen(str_arg + i) > 1
                && str_arg[i] == '-' && ft_isdigit(str_arg[i + 1])))
    {
        arg = ft_atoi(str_arg + i);
		if (SIZE(CMD) == ON)
		{
			if (arg >= INT16_MIN && arg <= INT16_MAX)
				return (OKAY);
			else
				return (ft_error_int(file, ERROR_T_DIR));
		}
		return (OKAY);
    }
    return (ERROR);
}

int			check_arg_ind(t_core *file, t_cmd *c, char *str_arg)
{
    int		i;
	int 	len;
    int		arg;

    i = 0;
    if (!file || !c || !str_arg)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (str_arg[i] == LABEL_CHAR)
		return (check_arg_label(file, c, str_arg));
	len = (int)ft_strlen(str_arg);
	while (i < len)
	{
		if (i == 0 && str_arg[i] == '-')
			i++;
		if (ft_strchr("01234567890", str_arg[i]))
			i++;
		else
			return (ft_error_int(file, ERROR_T_IND));
	}
	i = 0;
    if (ft_isdigit(str_arg[i]) || (ft_strlen(str_arg + i) > 1
           && str_arg[i] == '-' && ft_isdigit(str_arg[i + 1])))
    {
        arg = ft_atoi(str_arg + i);
		return (OKAY);
    }
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
