/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:32:56 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/25 18:33:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*mas;
	const unsigned char	*source;

	i = 0;
	mas = (unsigned char *)dst;
	source = src;
	while (i < n)
	{
		mas[i] = source[i];
		if (source[i] == (unsigned char)c)
			return (dst + (i + 1));
		i++;
	}
	return (NULL);
}
