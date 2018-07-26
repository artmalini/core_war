/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:28:06 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/30 17:28:12 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*mas;
	int		len;
	int		del;

	if (ft_minint(n))
		return (ft_strdup("-2147483648"));
	len = ft_int_length(n);
	del = n;
	if (n < 0)
		len++;
	if ((mas = ft_strnew(len)) == NULL)
		return (NULL);
	if (n < 0)
		n = -n;
	*(mas + --len) = (n % 10) + '0';
	while (n /= 10)
		*(mas + --len) = (n % 10) + '0';
	if (del < 0)
		*(mas + 0) = '-';
	return (mas);
}
