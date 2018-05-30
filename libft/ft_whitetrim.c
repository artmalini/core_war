/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitetrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:06:30 by amakhiny          #+#    #+#             */
/*   Updated: 2017/11/12 17:08:26 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_whitetrim(char const *s, size_t begin)
{
	size_t		j;
	size_t		last;

	if (s || begin)
	{
		j = 0;
		last = ft_strlen(s) - 1;
		while ((s[last] == ' ' || s[last] == '\n' || s[last] == '\t'))
		{
			j++;
			last--;
		}
		return (j);
	}
	return (0);
}
