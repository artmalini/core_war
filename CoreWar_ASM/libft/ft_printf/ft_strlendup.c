/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlendup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:48:00 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 11:48:05 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strlendup(const char *str1, int len)
{
	char	*str;

	if (str1)
	{
		if (!(str = (char *)malloc(sizeof(str) * (len + 1))))
			return (NULL);
		if (str)
			str = ft_strncpy(str, str1, len);
	}
	else
		str = NULL;
	return (str);
}
