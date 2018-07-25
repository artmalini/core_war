/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 11:49:36 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/04 11:50:53 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinstr(char *str1, char *str2)
{
	char 	*str3;

	if (!str1 || !str2)
		return (NULL);
	str3 = (char *)malloc(sizeof(str3) * ((ft_strlen(str1)) + (ft_strlen(str2))) + 1);
	if (!str3)
		return (NULL);
	*str3 = 0;
	str3 = ft_strcat(ft_strcat(str3, str1), str2);
	free(str1);
	free(str2);
	return (str3);
}
