/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:55:29 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/25 21:55:45 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cmp1;
	unsigned char	*cmp2;
	size_t			i;

	i = 0;
	cmp1 = (unsigned char *)s1;
	cmp2 = (unsigned char *)s2;
	while (i < n)
	{
		if (cmp1[i] != cmp2[i])
			return (cmp1[i] - cmp2[i]);
		i++;
	}
	return (0);
}
