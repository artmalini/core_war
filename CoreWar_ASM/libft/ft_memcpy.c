/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:15:22 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/25 18:15:26 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*mas;
	const unsigned char	*source;

	i = 0;
	mas = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (mas != src || n != 0)
	{
		while (i < n)
		{
			mas[i] = source[i];
			i++;
		}
	}
	return (dst);
}
