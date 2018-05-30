/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:01:49 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/22 12:01:55 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	prf_print_str_ln(char *str, int nbr)
{
	if (str && nbr)
		write(1, str, nbr);
}

int		prf_putchar(char c)
{
	if (c)
	{
		write(1, &c, 1);
		return (1);
	}
	return (0);
}

int		prf_nbr_putchar(char c, int nbr)
{
	int		len;

	len = 0;
	while (nbr > 0)
	{
		write(1, &c, 1);
		len++;
		nbr--;
	}
	return (len);
}

int		prf_putstr(char *str)
{
	int		len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
		write(1, str, len);
	}
	return (len);
}

int		ft_char(char *str)
{
	int		len;

	len = 0;
	if (str)
	{
		len++;
		write(1, &(*str), 1);
		free(str);
	}
	return (len);
}
