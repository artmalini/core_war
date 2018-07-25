/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:41:19 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 11:43:24 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*str_join_float(char *str1, char *str2)
{
	char	*str3;
	int		len1;
	int		len2;

	if (!str1 || !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!(str3 = (char *)malloc(sizeof(str3) * ((len1 + len2) + 1))))
		return (NULL);
	*str3 = 0;
	str3 = ft_strcat(ft_strcat(str3, str1), str2);
	free(str1);
	free(str2);
	return (str3);
}
