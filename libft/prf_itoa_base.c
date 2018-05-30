/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prf_itoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:24:11 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 14:24:25 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		find_biglen(t_bone *elem, uintmax_t bighigh, int len)
{
	while (bighigh /= elem->base)
		len++;
	return (len);
}

int		chk_o(t_bone *elem, int tmplen, uintmax_t big)
{
	if (elem->hex && big == 0)
		return (chk_o_min(elem));
	if (elem->hex && big > 0 && elem->precis > 0)
	{
		if ((elem->minus == 1 || (elem->width == 0 && elem->hex))
			&& elem->sign == '-')
		{
			if (elem->minus == 1 && elem->mod_l != 0)
				return (1);
			hex_free(elem);
		}
		if (((elem->width > 0 || elem->precis > 0) && elem->sign != '-'))
		{
			if (elem->precis <= find_biglen(elem, big, 1))
				return (1);
			hex_free(elem);
		}
		return (1);
	}
	if ((elem->precis != 0 || tmplen > 1))
		return (1);
	return (0);
}

int		chk_x_min(t_bone *elem, uintmax_t big)
{
	if (elem->mod_l <= 0 || elem->width > 0)
	{
		hex_free(elem);
		if (elem->precis == 0)
			return (0);
		return (1);
	}
	if (elem->mod_l > 0)
	{
		hex_free(elem);
		if (elem->precis == 0)
			return (0);
		if (elem->precis > 0)
			return (1);
	}
	if (big == 0 && elem->precis == 0 && elem->mod_l != -1)
		return (0);
	return (1);
}

int		check_val(t_bone *elem, int tmplen, uintmax_t big)
{
	if (ft_strchr("oO", elem->type))
		return (chk_o(elem, tmplen, big));
	if (ft_strchr("xX", elem->type) && elem->hex && big == 0)
		return (chk_x_min(elem, big));
	if (ft_strchr("xX", elem->type) && elem->hex)
	{
		if (elem->mod_l <= 1 && elem->precis <= 0 && big == 0)
		{
			hex_free(elem);
			return (0);
		}
		return (1);
	}
	if ((elem->precis != 0 || tmplen > 1) || (ft_strchr("fFeEaA", elem->type)))
		return (1);
	return (0);
}

char	*prf_itoa_base(t_bone *elem, uintmax_t bighigh, int len)
{
	uintmax_t	big;
	int			tmplen;
	char		*itoa;
	char		*str;
	int			i;

	str = "0123456789abcdef0123456789ABCDEF";
	str += 16 * elem->xx;
	i = 0;
	len = find_biglen(elem, bighigh, len);
	tmplen = len;
	itoa = NULL;
	big = bighigh;
	len = (len > elem->precis) ? len : elem->precis;
	itoa = ft_memalloc(len + 1);
	while (i < len && check_val(elem, tmplen, big))
	{
		*(itoa + --len) = str[bighigh % elem->base];
		bighigh /= elem->base;
	}
	return (itoa);
}
