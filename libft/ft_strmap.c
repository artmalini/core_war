/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:11:58 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/27 22:12:04 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	ln;
	char	*mas;

	i = 0;
	if (!s || !f)
		return (NULL);
	ln = ft_strlen(s);
	if (!(mas = ft_strnew(ln)))
		return (NULL);
	while (s[i] != '\0')
	{
		mas[i] = f(s[i]);
		i++;
	}
	mas[i] = '\0';
	return (mas);
}
