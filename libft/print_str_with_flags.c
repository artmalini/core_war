/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_with_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:01:07 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 13:01:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		if_flag(t_bone *elem, int nb)
{
	int		len;

	len = nb;
	if (elem->flag)
		len++;
	return (len);
}

int		print_str_with_flags(char *str, t_bone *elem, int nb)
{
	int		len;

	len = 0;
	nb = (elem->hex) ? nb + ft_strlen(elem->hex) : nb;
	if (elem->padding == '0')
	{
		len = elem->flag ? prf_putchar(elem->flag) : 0;
		len += (elem->hex ? prf_putstr(elem->hex) : 0);
	}
	if (!elem->left)
		len += prf_nbr_putchar(elem->padding, elem->width - if_flag(elem, nb));
	if (elem->padding == ' ')
	{
		len += elem->flag ? prf_putchar(elem->flag) : 0;
		len += elem->hex ? prf_putstr(elem->hex) : 0;
	}
	if (!ft_strcmp("(null)", str))
		prf_print_str_ln(str, elem->precis != -1 ?
			ft_strlen(str) - elem->precis : ft_strlen(str));
	else
		prf_print_str_ln(str, ft_strlen(str));
	if (elem->left)
		len += prf_nbr_putchar(elem->padding, elem->width - if_flag(elem, nb));
	free(str);
	return (len);
}
