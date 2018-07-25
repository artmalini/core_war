/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:19:52 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/28 12:19:55 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*mas;

	if (!s)
		return (NULL);
	if (!(mas = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
		mas[i++] = s[start++];
	mas[i] = '\0';
	return (mas);
}
