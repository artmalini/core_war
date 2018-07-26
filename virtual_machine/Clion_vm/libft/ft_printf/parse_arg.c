/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:45:23 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 13:45:27 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		c_type(va_list arg, t_bone *elem, char *str, int len)
{
	int		clen;

	if (!(str = build_char(arg, elem)))
		return (0);
	len += ((ft_strlen(str) == 0) ? 0 : ft_strlen(str));
	clen = len;
	if (clen == 0 && !elem->left)
		len += prf_nbr_putchar(elem->padding, elem->width - 1);
	len += ft_strlen(str) > 0 ?
		print_str_with_flags(str, elem, len) : ft_char(str);
	if (clen == 0 && elem->left == 1)
		len += prf_nbr_putchar(elem->padding, elem->width - 1);
	return (len);
}

int		s_type(va_list arg, t_bone *elem, char *str, int len)
{
	str = build_str_char(arg, elem);
	if (!ft_strcmp("(null)", str))
		len += elem->precis != -1 ? ft_strlen(str) - elem->precis :
				ft_strlen(str);
	else
		len += ft_strlen(str);
	len += print_str_with_flags(str, elem, len);
	return (len);
}

int		none_spec(t_bone *elem, char *str, int len)
{
	*str = elem->type;
	len++;
	if (elem->type && !ft_strchr("0", elem->type))
		len += print_str_with_flags(str, elem, 1);
	else
	{
		len = 0;
		free(str);
	}
	return (len);
}

int		parse_arg(va_list arg, t_bone *elem, int ln)
{
	int		len;
	char	*str;

	len = 0;
	str = NULL;
	if (elem->type && ft_strchr("cC", elem->type))
		len = c_type(arg, elem, str, len);
	else if (elem->type && ft_strchr("sS", elem->type))
		len = s_type(arg, elem, str, len);
	else if (elem->type && ft_strchr("pdDioOuUxXb", elem->type) && arg)
		len += print_atoi_nbr(arg, elem);
	else if (elem->type && ft_strchr("fFeEaA", elem->type))
		len += print_floate_nbr(arg, elem);
	else if (elem->type == 'n')
		return (*va_arg(arg, int*) = ln);
	else if ((str = ft_memalloc(2)))
		len = none_spec(elem, str, len);
	return (len);
}
