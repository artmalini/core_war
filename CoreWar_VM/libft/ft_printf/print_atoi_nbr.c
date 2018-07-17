/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_atoi_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:37:48 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 12:37:52 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				parse_atoi_arg(t_bone *elem, uintmax_t bighigh, int len)
{
	char	*str;

	str = NULL;
	str = prf_itoa_base(elem, bighigh, 1);
	len = ft_strlen(str);
	len += print_str_with_flags(str, elem, len);
	return (len);
}

uintmax_t		min_bigmin(t_bone *elem, va_list arg)
{
	uintmax_t	bighigh;
	intmax_t	bigmin;

	bigmin = intmax_cast(va_arg(arg, intmax_t), elem);
	if (bigmin < 0)
	{
		bighigh = -bigmin;
		elem->flag = '-';
	}
	else
		bighigh = bigmin;
	return (bighigh);
}

int				print_atoi_nbr(va_list arg, t_bone *elem)
{
	uintmax_t	bighigh;
	int			len;

	len = 0;
	if (elem->type && ft_strchr("dDi", elem->type))
		bighigh = min_bigmin(elem, arg);
	else
		bighigh = uintmax_cast(va_arg(arg, uintmax_t), elem);
	if (bighigh > 4294000000 && ft_strchr("oO", elem->type))
		elem->sign = '-';
	if ((bighigh == 0 && elem->precis == 0 && elem->width == 0 &&
		elem->mod_l == -1) && (elem->type && !ft_strchr("poO", elem->type)))
	{
		if (elem->flag != 0 || ft_strchr("oO", elem->type))
			len += parse_atoi_arg(elem, bighigh, len);
		return (len);
	}
	else
		len += parse_atoi_arg(elem, bighigh, len);
	return (len);
}
