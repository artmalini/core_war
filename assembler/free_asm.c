/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 22:57:56 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 22:57:58 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_atoii(const char *str)
{
    int					sign;
    unsigned long int	res;

    res = 0;
    sign = 1;
    while (ft_isspace(*str))
        str++;
    if (*str == '-' && ft_isdigit(*(str + 1)))
    {
        sign = -1;
        str++;
    }
    if (*str == '+' && ft_isdigit(*(str + 1)))
        str++;
    while (ft_isdigit(*str) && *str)
    {
        res = res * 10 + ((int)*str++ - '0');
        if (res >= 9223372036854775807 && sign == 1)
            return (-1);
        else if (res > 9223372036854775807 && sign == -1)
            return (0);
    }
    return ((int)(res * sign));
}

int		ft_isspace(char c)
{
    if (c == ' ')
        return (1);
    if (c == '\t')
        return (2);
    if (c == '\v')
        return (3);
    if (c == '\n')
        return (4);
    if (c == '\f')
        return (5);
    if (c == '\r')
        return (6);
    return (0);
}

void	free_mas(char **mas)
{
    int i;

    i = -1;
    if (!mas)
        return ;
    while (mas[++i] != NULL)
        free(mas[i]);
    free(mas);
}
