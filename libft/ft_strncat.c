/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:32:51 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/26 14:32:56 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*mas;
	int		ln;
	int		i;

	mas = s1;
	ln = 0;
	i = 0;
	while (mas[ln] != '\0')
		ln++;
	while (n-- > 0 && s2[i] != '\0')
	{
		mas[ln++] = s2[i++];
	}
	mas[ln] = '\0';
	return (mas);
}
