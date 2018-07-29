/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:14:23 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/25 15:14:30 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*myval;
	size_t			i;

	myval = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		myval[i] = 0;
		i++;
	}
}
