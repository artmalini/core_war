/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_flag_with_precis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:13:24 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 11:13:28 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_flag(const char **f, t_bone *elem)
{
	while (**f == '+' || **f == ' ' || **f == '-' || **f == '0' || **f == '#')
	{
		if (**f == '+')
			elem->flag = '+';
		else if (**f == ' ')
			elem->flag = (elem->flag == 0 ? ' ' : elem->flag);
		else if (**f == '-')
		{
			elem->left = 1;
			elem->padding = ' ';
			if (elem->minus == -1 && g_flag == 0)
				elem->minus = 1;
		}
		else if (**f == '0')
			elem->padding = (elem->left == 0 ? '0' : elem->padding);
		else if (**f == '#')
		{
			hex_free(elem);
			elem->hex = ft_strdup("#");
			g_flag++;
			elem->sign = '#';
		}
		(*f)++;
	}
}

void	fill_width(const char **format, va_list arg, t_bone *elem)
{
	while (**format == '*')
	{
		elem->width = 0;
		if ((elem->width = va_arg(arg, int)) < 0)
		{
			elem->width = elem->width * -1;
			elem->left = 1;
			elem->padding = ' ';
		}
		(*format)++;
	}
	if (**format >= '1' && **format <= '9')
	{
		elem->width = 0;
		while (**format >= '0' && **format <= '9')
		{
			elem->width = elem->width * 10 + **format - '0';
			(*format)++;
		}
	}
	fill_flag(format, elem);
}

void	fill_precis(const char **format, va_list arg, t_bone *elem)
{
	while (**format == '.')
	{
		elem->precis = 0;
		(*format)++;
		if (**format == '*')
		{
			elem->precis = va_arg(arg, int);
			elem->minus = 0;
			if (elem->precis < 0)
				elem->precis = -1;
			(*format)++;
		}
		else
		{
			while (**format >= '0' && **format <= '9')
			{
				elem->precis = elem->precis * 10 + **format - '0';
				(*format)++;
			}
		}
	}
	fill_width(format, arg, elem);
}
