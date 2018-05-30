/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:33:12 by amakhiny          #+#    #+#             */
/*   Updated: 2017/12/12 11:33:29 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/get_next_line.h"

static t_mem	*readbuff(t_mem *lst, const int fd)
{
	t_mem			*elem;

	elem = lst;
	while (elem)
	{
		if (elem->fd == fd)
			break ;
		elem = elem->next;
	}
	if (!elem)
	{
		if (!(elem = (t_mem *)malloc(sizeof(t_mem))))
			return (0);
		if (!(elem->content = ft_strnew(0)))
			return (0);
		elem->fd = fd;
		elem->next = NULL;
		while (lst && lst->next)
			lst = lst->next;
		if (lst)
			lst->next = elem;
	}
	return (elem);
}

static int		get_line(t_mem *lst, char **line)
{
	char	*temp;
	char	*ret;

	if (!(temp = ft_strdup(lst->content)))
		return (-1);
	free(lst->content);
	if (*temp == '\n')
	{
		if (!(*line = ft_strnew(0)) ||
			!(lst->content = ft_strdup(temp + 1)))
			return (-1);
		free(temp);
		return (1);
	}
	if ((ret = ft_strchr(temp, '\n')))
	{
		if (!(lst->content = ft_strdup(ret + 1)))
			return (-1);
		*ret = '\0';
	}
	else
		lst->content = ft_strnew(0);
	ret = temp;
	*line = ret;
	return (!*ret ? 0 : 1);
}

int				get_next_line(const int fd, char **line)
{
	static t_mem	*mem;
	t_mem			*lst;
	int				val;
	char			*box;
	char			buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || !(lst = readbuff(mem, fd)) || BUFF_SIZE < 1)
		return (-1);
	if (!mem)
		mem = lst;
	while ((val = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[val] = '\0';
		if (!(box = ft_strjoin(lst->content, buff)))
			return (-1);
		free(lst->content);
		lst->content = box;
		if (ft_strchr(lst->content, '\n'))
			return (get_line(lst, line));
	}
	if (val == -1)
		return (-1);
	return (get_line(lst, line));
}
