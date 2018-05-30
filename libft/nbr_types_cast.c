/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_types_cast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:54:22 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 12:54:25 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

intmax_t		nbr_z(intmax_t num)
{
	if (sizeof(size_t) == sizeof(short))
		return ((short)num);
	else if (sizeof(size_t) == sizeof(int))
		return ((int)num);
	else if (sizeof(size_t) == sizeof(long))
		return ((long long)num);
	else if (sizeof(size_t) == sizeof(long long))
		return ((long long)num);
	else
		return (num);
}

intmax_t		intmax_cast(uintmax_t nbr, t_bone *elem)
{
	if (elem->mod_l != -1)
	{
		if (elem->mod_l == 0)
			return ((char)nbr);
		else if (elem->mod_l == 1)
			return ((short)nbr);
		else if (elem->mod_l == 2)
			return ((long)nbr);
		else if (elem->mod_l == 3)
			return ((long long)nbr);
		else if (elem->mod_l == 5)
			return (nbr);
		else if (elem->mod_l == 6)
			return (nbr_z(nbr));
	}
	return ((int)nbr);
}

uintmax_t		uintmax_cast(uintmax_t nbr, t_bone *elem)
{
	if (elem->mod_l != -1)
	{
		if (elem->mod_l == 0)
			return ((unsigned char)nbr);
		else if (elem->mod_l == 1)
			return ((unsigned short)nbr);
		else if (elem->mod_l == 2)
			return ((unsigned long)nbr);
		else if (elem->mod_l == 3)
			return ((unsigned long long)nbr);
		else if (elem->mod_l == 5)
			return (nbr);
		else if (elem->mod_l == 6)
			return ((size_t)nbr);
	}
	else if (elem->type == 'p')
		return (nbr);
	return ((unsigned int)nbr);
}
