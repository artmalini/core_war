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
