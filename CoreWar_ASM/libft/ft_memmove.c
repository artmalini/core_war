/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:11:15 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/25 19:11:38 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*mas;
	const unsigned char		*sourc;

	mas = (unsigned char *)dst;
	sourc = (unsigned char *)src;
	if (mas != src || len != 0)
	{
		if (mas <= sourc || sourc >= (mas + len))
		{
			while (len-- > 0)
				*mas++ = *sourc++;
		}
		else
		{
			mas = mas + len - 1;
			sourc = sourc + len - 1;
			while (len-- > 0)
				*mas-- = *sourc--;
		}
	}
	return (dst);
}
