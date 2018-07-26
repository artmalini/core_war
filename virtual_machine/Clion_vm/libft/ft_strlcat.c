/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:54:41 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/26 14:54:46 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		len_dst;
	size_t		len_size;
	size_t		i;
	size_t		j;

	len_dst = ft_strlen(dst);
	len_size = ft_strlen(src);
	i = len_dst;
	j = 0;
	if (size < len_dst + 1)
		return (len_size + size);
	while (i < size - 1)
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
	return (len_size + len_dst);
}
