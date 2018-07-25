/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:43:44 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/26 13:43:49 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*mas;
	int		ln;
	int		i;

	mas = s1;
	ln = 0;
	i = 0;
	while (mas[ln] != '\0')
		ln++;
	while (s2[i] != '\0')
	{
		mas[ln] = s2[i];
		i++;
		ln++;
	}
	mas[ln] = '\0';
	return (mas);
}
