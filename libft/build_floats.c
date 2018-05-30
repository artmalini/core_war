/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_floats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:16:18 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 13:16:21 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char		*xx_upper(char *s)
{
	char	*str;

	str = s;
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'p')
			*str -= 32;
		str++;
	}
	return (s);
}

char		*suffix_ep(char *str, long double tmp_nbr, int nmbase)
{
	char	*str1;

	str1 = NULL;
	str1 = str_join_float(str, (nmbase != 2) ?
			ft_strdup("e") : ft_strdup("p"));
	str1 = str_join_float(str1, ((tmp_nbr >= 1 || tmp_nbr == 0) ?
			ft_strdup("+") : ft_strdup("-")));
	return (str1);
}

char		*advanc_floats(t_bone *elem, long double nbr, char *str, int nmbase)
{
	int				tick;
	long double		l;
	long double		tmp_nbr;

	tick = 0;
	l = 1;
	tmp_nbr = nbr;
	if (nbr >= 1)
		while ((nbr / l >= nmbase) && ++tick)
			l *= nmbase;
	else
		while ((nbr && nbr / l < 1) && ++tick)
			l /= nmbase;
	if (!(str = build_mantissa(elem, tmp_nbr / l, 1)))
		return (NULL);
	nbr = build_float(elem, tmp_nbr / l);
	if (elem->precis == -1 && (tick != 0 && nmbase == 2 && nbr > 0))
		str = str_join_float(str, ft_strdup("."));
	str = str_join_float(str, build_float_join_str(elem, nbr));
	str = suffix_ep(str, tmp_nbr, nmbase);
	if (tick < 10 && nmbase != 2)
		str = str_join_float(str, ft_strdup("0"));
	elem->base = 10;
	str = str_join_float(str, prf_itoa_base(elem, tick, 1));
	return ((elem->xx == 1) ? xx_upper(str) : str);
}

/*
** fFgGaA
*/

char		*build_float_str(t_bone *elem, long double nbr, char *str)
{
	int		nmbase;

	nmbase = (ft_strchr("aA", elem->type) ? 2 : elem->base);
	if (elem->type && ft_strchr("fF", elem->type))
	{
		str = build_mantissa(elem, nbr, 1);
		if (!str)
		{
			str = ft_strdup("inf");
			return ((ft_strchr("F", elem->type)) ? xx_upper(str) : str);
		}
		nbr = build_float(elem, nbr);
		str = str_join_float(str, build_float_join_str(elem, nbr));
	}
	else
	{
		str = advanc_floats(elem, nbr, str, nmbase);
		if (!str)
		{
			hex_free(elem);
			str = ft_strdup("inf");
			return ((elem->xx == 1) ? xx_upper(str) : str);
		}
	}
	return (str);
}

int			print_floate_nbr(va_list arg, t_bone *elem)
{
	int				len;
	long double		nbr;
	char			*str;

	len = 0;
	nbr = 0;
	str = NULL;
	if (elem->mod_l != -1 && elem->mod_l == 4)
		nbr = va_arg(arg, long double);
	else
		nbr = va_arg(arg, double);
	elem->flag = (nbr < 0) ? '-' : elem->flag;
	nbr = (nbr < 0) ? -nbr : nbr;
	elem->precis = (elem->precis == -1 && !ft_strchr("aA", elem->type))
					? 6 : elem->precis;
	if ((str = build_float_str(elem, nbr, str)))
	{
		len = ft_strlen(str);
		len += print_str_with_flags(str, elem, len);
	}
	return (len);
}
