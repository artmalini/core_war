/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:04:40 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:04:42 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_file(char *arg, t_core *file)
{
	char	*line;
	int		fd;

	if (!(fd = open(arg, O_RDONLY)))
		wrong_input(3);
	while (get_next_line(fd, &line))
	{
		file->rows++;
		if (line_has_val(line))
			read_line(line, file);
		else
			ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
}

int		parse_filename(char	*arg, t_core *file)
{
	int		len;
	int		i;
	int		l;

	len = ft_strlen(arg);
	i = -1;
	if ((arg[len - 1] != 's' || arg[len - 2] != '.') || len < 3)
		wrong_input(2);
	l = len - 1;
	file->filename = (char*)malloc(sizeof(t_core) * (len + 4));
	while (++i < l)
		file->filename[i] = arg[i];
	file->filename[i++] = 'c';
	file->filename[i++] = 'o';
	file->filename[i++] = 'r';
	file->filename[i] = '\0';
	//ft_printf("filename %s\n",file->filename);
	return (1);
}