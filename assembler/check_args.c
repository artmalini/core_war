/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:30:41 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/08 15:30:43 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			    check_arg_label(t_core *file, char *str_arg, int nbr_arg)
{
    int         i;

    i = 0;
    if (!file || !str_arg || nbr_arg <= 0)
    {
        error_cor(file, ERROR_ARG);
        return (ERROR);
    }
    while (str_arg[i] && ft_isspace(str_arg[i]))                                //Pass Spaces
        i++;
    if (str_arg[i] == '%')
        i++;
    if (str_arg[i] == ':')
    {
        i++;
        while (str_arg[i] && ft_strchr(LABEL_CHARS, str_arg[i]))
            i++;
        if (str_arg[i] == '\0')
            return (OK);
    }
    return (ERROR);
}

int			    check_arg_reg(t_core *file, char *str_arg, int nbr_arg)
{
    int         i;
    int         hex;

    i = 0;
    hex = ERROR;
    if (!file || !str_arg || nbr_arg <= 0)
    {
        error_cor(file, ERROR_ARG);
        return (ERROR);
    }
    while (str_arg[i] && ft_isspace(str_arg[i]))                                //Pass Spaces
        i++;
    if (ft_strlen(str_arg + i) > 1 && str_arg[i++] == 'r')                      //Valid diapason [1;15]
    {
        if (ft_isdigit(str_arg[i]))
            hex = ft_atoi(str_arg + i);
        if (hex > 0 && hex <= REG_NUMBER)
            return (OK);
    }
    return (ERROR);
}

int			    check_arg_dir(t_core *file, char *str_arg, int nbr_arg)
{
    int         i;
    int         arg;

    i = 0;
    if (!file || !str_arg || nbr_arg <= 0)
    {
        error_cor(file, ERROR_ARG);
        return (ERROR);
    }
    while (str_arg[i] && ft_isspace(str_arg[i]))                                //Pass Spaces
        i++;
    if (str_arg[i] == '%')
        i++;
    if (str_arg[i] == ':')
        return (check_arg_label(file, str_arg, nbr_arg));
    else if (ft_isdigit(str_arg[i]) || (ft_strlen(str_arg + i) > 1
                && str_arg[i] == '-' && ft_isdigit(str_arg[i + 1])))
    {
        arg = ft_atoi(str_arg + i);
        if (arg >= INT16_MIN && arg <= INT16_MAX)                                   //For 2-Byte Integer
            return (OK);
        else if (arg >= INT32_MIN && arg <= INT32_MAX)                              //For 4-Byte Integer
            return (OK);
    }
    return (ERROR);
}

int			    check_arg_ind(t_core *file, char *str_arg, int nbr_arg)
{
    int         i;
    int         arg;

    i = 0;
    if (!file || !str_arg || nbr_arg <= 0)
    {
        error_cor(file, ERROR_ARG);
        return (ERROR);
    }
    while (str_arg[i] && ft_isspace(str_arg[i]))                                //Pass Spaces
        i++;
    if (ft_isdigit(str_arg[i]) || (ft_strlen(str_arg + i) > 1
           && str_arg[i] == '-' && ft_isdigit(str_arg[i + 1])))
    {
        arg = (short)ft_atoi(str_arg + i);                                      //Cast to short integer
        if (arg >= INT16_MIN && arg <= INT16_MAX)
            return (OK);
    }
    return (ERROR);
}

int 		    check_args_main(t_core *file, char **args, int nbr_args)
{
    int         i;
    int         nbr;
    int         status;

    nbr = 0;
    status = OK;
    while (nbr_args > nbr && args[nbr])
    {
        i = 0;
        while (args[nbr][i] && ft_isspace(args[nbr][i]))                        //Pass Spaces
            i++;
        if (args[nbr][i] == 'r')
            status = check_arg_reg(file, args[nbr], (nbr + 1));                 //Check T_REG = DONE
        else if (args[nbr][i] == '%')
            status = check_arg_dir(file, args[nbr], (nbr + 1));                 //Check T_DIR = Need label for 2/4 byte INTEGER
        else if (args[nbr][i] == ':')
            status = check_arg_label(file, args[nbr], (nbr + 1));                //Check T_IND = DONE
        else if (ft_isdigit(args[nbr][i]) || args[nbr][i] == '-')
            status = check_arg_ind(file, args[nbr], (nbr + 1));
        if (status != OK)
            return (ERROR);
        nbr++;
    }
    return (OK);
}

