/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:30:41 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/08 15:30:43 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void        set_settings(t_core	*file, int flag)
{
    if (flag == ON)
    {
        file->st[DEBUG_ON] = ON;
        file->st[DEBUG_ARG] = ON;
        file->st[DEBUG_CMD] = ON;
        file->st[DEBUG_LB] = ON;
    }
}