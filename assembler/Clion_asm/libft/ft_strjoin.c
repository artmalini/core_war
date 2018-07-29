/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 13:30:58 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/28 13:31:01 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mas;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(mas = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		mas[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
	{
		mas[i] = s2[j];
		i++;
	}
	mas[i] = '\0';
	return (mas);
}
