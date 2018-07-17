/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:54:00 by amakhiny          #+#    #+#             */
/*   Updated: 2017/10/28 16:54:36 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		freesplit(char **mas, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		free(mas[i]);
		i++;
	}
	free(mas);
	mas = NULL;
}

static char		**ft_finalize(char **mas, char const *s, char c, int len)
{
	int		i;
	int		k;

	i = 0;
	while (i < len)
	{
		k = 0;
		if (!(*(mas + i) = (char *)malloc(ft_getword_len(s, c) + 1)))
		{
			freesplit(mas, len);
			return (NULL);
		}
		while (*s == c)
			s++;
		while (*s != c && *s)
			*(*(mas + i) + k++) = (char)*s++;
		*(*(mas + i) + k) = '\0';
		i++;
	}
	*(mas + i) = 0;
	return (mas);
}

char			**ft_strsplit(char const *s, char c)
{
	int		len;
	char	**mas;
	char	**split;

	if (!s)
		return (NULL);
	len = ft_count_words(s, c);
	if (!(mas = (char **)malloc(sizeof(*mas) * (len + 1))))
		return (NULL);
	split = ft_finalize(mas, s, c, len);
	return (split);
}
