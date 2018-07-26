/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_char_strchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:07:23 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 12:07:27 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*utf_char_unicode(wchar_t c)
{
	char	*str;
	char	*e;

	str = ft_memalloc(5);
	if ((e = str) && c <= 0x7F)
		e[0] = c;
	else if (c <= 0x7FF)
	{
		e[0] = (c >> 6) | 0xC0;
		e[1] = (c & 0x3F) | 0x80;
	}
	else if (c <= 0xFFFF)
	{
		e[0] = (c >> 12) | 0xE0;
		e[1] = ((c >> 6) & 0x3F) | 0x80;
		e[2] = (c & 0x3F) | 0x80;
	}
	else if (c <= 0x10FFFF)
	{
		e[0] = (c >> 18) | 0xF0;
		e[1] = ((c >> 12) & 0x3F) | 0x80;
		e[2] = ((c >> 6) & 0x3F) | 0x80;
		e[3] = (c & 0x3F) | 0x80;
	}
	return (str);
}

char	*utf_char_len_concat(wchar_t *symb, int len)
{
	char	*str;
	char	*utf_str;
	int		nbr;

	if (symb && (str = ft_memalloc((len + 1))))
	{
		nbr = len;
		while (*symb)
		{
			utf_str = utf_char_unicode(*symb);
			nbr -= ft_strlen(utf_str);
			if (nbr < 0)
				break ;
			str = ft_strcat(str, utf_str);
			if (utf_str)
				free(utf_str);
			symb++;
		}
	}
	else
		str = NULL;
	return (str);
}

char	*utf_char_find_len_concat(wchar_t *c)
{
	int			len;
	char		*str;
	wchar_t		*symb;

	len = 0;
	symb = c;
	if (symb)
		while (*symb)
		{
			len += sizeof(wchar_t);
			symb++;
		}
	str = utf_char_len_concat(c, len);
	return (str);
}

char	*build_char(va_list arg, t_bone *elem)
{
	char	*str;

	str = NULL;
	if (elem->mod_l != -1 && elem->mod_l == 2 && MB_CUR_MAX > 1)
		str = utf_char_unicode((wchar_t)va_arg(arg, wint_t));
	else
	{
		if (!(str = ft_memalloc(2)))
			return (NULL);
		*str = (char)va_arg(arg, int);
	}
	return (str);
}

char	*build_str_char(va_list arg, t_bone *elem)
{
	char	*str;

	str = NULL;
	if (elem->mod_l != -1 && elem->mod_l == 2)
	{
		if (elem->precis >= 0)
			str = utf_char_len_concat(va_arg(arg, wchar_t*), elem->precis);
		else
			str = utf_char_find_len_concat(va_arg(arg, wchar_t*));
	}
	else
	{
		if (elem->precis >= 0)
			str = ft_strlendup(va_arg(arg, char*), elem->precis);
		else
			str = ft_strdup(va_arg(arg, char*));
	}
	if (!str && elem->precis != 0)
		str = ft_strdup("(null)");
	else if (!str)
		str = ft_memalloc(sizeof(str));
	return (str);
}
