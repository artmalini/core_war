/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:31:36 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/27 13:32:02 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0' && --n > 0)
	{
		s1++;
		s2++;
	}
	if (n)
		return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
	return (0);
}
