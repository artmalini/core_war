/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:36:38 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/26 12:36:43 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*mas;

	mas = dst;
	while (*src != '\0' && len > 0)
	{
		*mas++ = *src++;
		--len;
	}
	if (len == 0)
		len++;
	while (len > 0)
	{
		*mas++ = '\0';
		--len;
	}
	return (dst);
}
