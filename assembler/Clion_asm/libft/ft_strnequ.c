/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:14:08 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/28 12:14:13 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = ft_strncmp(s1, s2, n);
	if (*s2 == 0 && n == 0)
		return (1);
	if (i == 0)
		return (1);
	return (0);
}
