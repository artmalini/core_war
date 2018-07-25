/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:36:07 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/26 20:11:18 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t		i;
	size_t		j;
	size_t		len1;
	size_t		len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(little);
	len2 = ft_strlen(big);
	if ((len1 == 0 && len2 != 0) || (len1 == 0 && len2 == 0))
		return ((char *)big);
	else if (len1 != 0 && len2 == 0)
		return (NULL);
	while (big[i] != '\0')
	{
		while (big[i + j] == little[j])
		{
			if (j == len1 - 1)
				return ((char *)big + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
