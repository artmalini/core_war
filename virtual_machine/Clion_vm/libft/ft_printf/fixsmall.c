/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:40:42 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/27 15:40:48 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hex_free(t_bone *elem)
{
	if (elem->hex)
	{
		free(elem->hex);
		elem->hex = NULL;
	}
}

int		chk_o_min(t_bone *elem)
{
	if (elem->precis > 0)
	{
		hex_free(elem);
		return (1);
	}
	return (0);
}
