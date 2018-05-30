/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_length_type_hex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:17:32 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 11:17:37 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		is_present(int i, t_bone *elem)
{
	int		j;

	j = -1;
	if (elem->mod_l == -1)
		return (1);
	while (++j < 7)
	{
		if (j == elem->mod_l)
		{
			if (i >= elem->mod_l)
				return (1);
		}
	}
	return (0);
}

/*
**				The length modifier
**			hh 	h 	l 	ll 	L 	j 	z t
** mask		0	1	2	3	4	5	 6
*/

void	fill_length(const char **format, t_bone *elem)
{
	while (**format && ft_strchr("hljzqLt", **format))
	{
		if ((**format == 'h' && (*format + 1)[0] == 'h') && is_present(0, elem))
		{
			elem->mod_l = 0;
			(*format)++;
		}
		if ((**format == 'h' && (*format - 1)[0] != 'h') && is_present(1, elem))
			elem->mod_l = 1;
		if ((**format == 'l' && (*format - 1)[0] != 'l') && is_present(2, elem))
			elem->mod_l = 2;
		if ((**format == 'l' && (*format + 1)[0] == 'l') && is_present(3, elem))
		{
			elem->mod_l = 3;
			(*format)++;
		}
		if (**format == 'L' && is_present(4, elem))
			elem->mod_l = 4;
		if (**format == 'j' && is_present(5, elem))
			elem->mod_l = 5;
		if ((**format == 'z' || **format == 't') && is_present(6, elem))
			elem->mod_l = 6;
		(*format)++;
	}
	fill_flag(format, elem);
}

void	fill_type(const char **format, t_bone *elem)
{
	if (**format && ft_strchr("sSpdDioOuUxXcCbfFeEaA", **format))
	{
		elem->xx = (ft_strchr("XEA", **format)) ? 1 : 0;
		elem->base = (ft_strchr("b", **format) ? 2 : elem->base);
		elem->base = (ft_strchr("oO", **format) ? 8 : elem->base);
		elem->base = (ft_strchr("pxXaA", **format) ? 16 : elem->base);
		if (**format && ft_strchr("DOUCS", **format))
			elem->mod_l = 2;
	}
	elem->flag = ((**format && !ft_strchr("dDifFfFeEaA", **format)) ?
				0 : elem->flag);
	elem->padding = ((**format && ft_strchr("pdDioOuUxXb", **format))
				&& (elem->precis >= 0)) ? ' ' : elem->padding;
	elem->type = **format;
}

void	fill_hex(const char **format, t_bone *elem)
{
	if (elem->hex || ft_strchr("paA", **format))
	{
		if (elem->hex)
			free(elem->hex);
		elem->hex = NULL;
		if (**format && ft_strchr("oO", **format))
			elem->hex = ft_strdup("0");
		else if (**format && ft_strchr("pxa", **format))
			elem->hex = ft_strdup("0x");
		else if (**format && ft_strchr("XA", **format))
			elem->hex = ft_strdup("0X");
		else if (**format == 'b')
			elem->hex = ft_strdup("0b");
		else
			elem->hex = NULL;
	}
	else
		elem->hex = NULL;
}
