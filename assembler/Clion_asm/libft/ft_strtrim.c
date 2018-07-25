/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:07:17 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/28 15:07:27 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t		j;
	size_t		i;
	size_t		begin;
	char		*mas;

	if (!s)
		return (NULL);
	begin = 0;
	while (*s != '\0' && (*s == ' ' || *s == '\t' || *s == '\n') && ++begin)
		s++;
	if (ft_strlen(s) == 0)
		return (ft_strdup(""));
	j = ft_whitetrim(s, begin);
	if (!(mas = ft_strnew(ft_strlen(s) - j)))
		return (NULL);
	i = 0;
	j = ft_strlen(s) - j;
	while (i < j)
		mas[i++] = *s++;
	mas[i] = '\0';
	return (mas);
}
