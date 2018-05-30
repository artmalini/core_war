/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_float_join_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:22:42 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 13:22:47 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*build_float_join_str(t_bone *elem, long double nbr)
{
	int		i;
	int		j;
	char	*str;

	j = elem->precis;
	elem->precis = 0;
	str = ft_memalloc(sizeof(str));
	while (j > 0 || (j < 0 && nbr))
	{
		i = nbr * elem->base;
		if (j == 1 && nbr >= .55)
			i++;
		if (i != -2147483648)
			str = str_join_float(str, prf_itoa_base(elem, i, 1));
		else
		{
			elem->precis = j;
			return (str_join_float(str, prf_itoa_base(elem, nbr, 1)));
		}
		nbr *= elem->base;
		nbr -= i;
		j--;
	}
	return (str);
}
