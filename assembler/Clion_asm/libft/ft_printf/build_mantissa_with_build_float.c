/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_mantissa_with_build_float.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:33:20 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 13:33:25 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		nbr_power(long double elmbase, long double power)
{
	long double i;
	long double num;

	i = 1;
	num = elmbase;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	while (i++ <= power)
		num *= elmbase;
	return (num);
}

long double		fix_droby_float(long double elmbase, long double nbr)
{
	long double		u;
	uintmax_t		i;

	u = 1;
	while (u < nbr / nbr_power(elmbase, 7))
		u *= nbr_power(elmbase, 7);
	while (nbr >= 1)
	{
		i = (uintmax_t)(nbr / u);
		nbr -= i * u;
		u /= nbr_power(elmbase, 7);
	}
	return (nbr);
}

long double		fix_droby(t_bone *elem, long double nbr, int i)
{
	long double		prefix;
	long double		first;

	i = elem->precis;
	if (elem->precis != -1)
	{
		first = fix_droby_float(elem->base, nbr);
		prefix = nbr - first;
		while (i-- > 0)
			first *= elem->base;
		if (fix_droby_float(elem->base, first) < .5)
		{
			first -= fix_droby_float(elem->base, first);
			first += .1;
		}
		else if (fix_droby_float(elem->base, first) >= .5)
		{
			first -= fix_droby_float(elem->base, first);
			first += 1.1;
		}
		while (++i < elem->precis)
			first /= elem->base;
		return (prefix + first);
	}
	return (nbr);
}

long double		build_float(t_bone *elem, long double droby)
{
	long double		val;
	long double		nbr;
	uintmax_t		i;

	val = 1;
	nbr = fix_droby(elem, droby, 0);
	while (nbr >= 1)
	{
		i = (uintmax_t)(nbr / val);
		if (i == 0)
			return (nbr);
		nbr -= i * val;
		if (i == 0)
			return (i);
		val /= 1;
	}
	return (nbr);
}

char			*build_mantissa(t_bone *elem, long double nbr, long double val)
{
	uintmax_t		i;
	int				tmp;
	char			*str;

	tmp = elem->precis;
	str = ft_memalloc(sizeof(str));
	elem->precis = 0;
	while (val < nbr / elem->base)
		val *= elem->base;
	while (val >= 1)
	{
		i = (uintmax_t)(nbr / val);
		if (i == 9223372036854775808U)
		{
			free(str);
			return (NULL);
		}
		str = str_join_float(str, prf_itoa_base(elem, i, 1));
		nbr -= i * val;
		val /= elem->base;
	}
	elem->precis = tmp;
	if (elem->precis > 0)
		str = str_join_float(str, ft_strdup("."));
	return (str);
}
