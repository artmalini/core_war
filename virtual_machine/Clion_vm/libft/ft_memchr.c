/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:47:19 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/25 21:47:24 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*val;
	size_t				i;

	val = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (val[i] == (unsigned char)c)
			return ((void *)val + i);
		i++;
	}
	return (NULL);
}
