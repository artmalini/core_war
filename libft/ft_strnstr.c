/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:56:27 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/26 21:56:36 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		ln;
	const char	*l;

	i = 0;
	j = 0;
	ln = 0;
	l = little;
	if (*little == 0 && *big != 0)
		return ((char*)big);
	while (big[i] != '\0' && i < len)
	{
		while (big[i] != '\0' && l[j] != '\0' && big[i] != l[j] && ++ln)
			i++;
		while ((big[i] != '\0' && l[j] != '\0') && (big[i] == l[j] && i < len))
		{
			j++;
			i++;
		}
		if (l[j] == '\0')
			return ((char *)big + ln);
	}
	return (NULL);
}
