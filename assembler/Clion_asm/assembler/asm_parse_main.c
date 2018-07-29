/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:04:40 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:04:42 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		read_init_line(t_core *file, char *line, int nb)
{
	char	*str;

	str = line;
	while (str && *str && ft_strchr(SPACES_CHARS, *str))
		str++;
	if (str && str[0] == '.')
	{
		file->point_nbr++;
		name_cmt_valid(file, str);
	}
	else if (str && (str[0] == COMMENT_CHAR || str[0] == COMMENT_CHAR2
					|| *str == '\0'))
	{
		ft_strdel(&line);
		return ;
	}
	else
	{
		nb = (file->name_nbr == 1 && file->cmt_nbr == 0) ? 1 : 2;
		name_cmt(file, str, nb);
	}
	if (file->syntax == 4)
		file->flag = ON;
	ft_strdel(&line);
}

void		parse_header(t_core *file, int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) && !file->flag)
	{
		file->error->current_rows++;
		if (!line_has_val(line))
			read_init_line(file, line, 0);
		else
			ft_strdel(&line);
	}
	ft_strdel(&line);
	if (file->syntax != 4)
		return (ft_error(file, ERROR_READ));
	rebuild_name_cmt(file, 0);
}

void		read_line(t_core *file, char *line)
{
	char	*str;

	str = line;
	while (str && *str && ft_strchr(SPACES_CHARS, *str))
		str++;
	if (str && (str[0] == COMMENT_CHAR || str[0] == COMMENT_CHAR2))
	{
		ft_strdel(&line);
		return ;
	}
	else
		line_handler(file, str, NULL);
	ft_strdel(&line);
}

void		parse_file(t_core *file, char *arg, char *line)
{
	int		fd;

	if (!(fd = open(arg, O_RDONLY)))
		return (ft_error(file, ERROR_OPEN));
	parse_header(file, fd);
	while (get_next_line(fd, &line))
	{
		file->error->current_rows++;
		if (line_has_val(line) == OKAY)
			read_line(file, line);
		else
			ft_strdel(&line);
	}
	ft_strdel(&line);
	if (close(fd) == ERROR)
		return (ft_error(file, ERROR_CLOSE));
}

int			parse_filename(t_core *file, char *arg, int len)
{
	int		i;
	int		l;

	i = -1;
	l = len - 1;
	if ((arg[len - 1] != 's' || arg[len - 2] != '.') || len < 3)
		return (ft_error_int(file, ERROR_READ));
	file->filename = ft_memalloc((size_t)len + 4);
	while (++i < l)
		file->filename[i] = arg[i];
	file->filename[i++] = 'c';
	file->filename[i++] = 'o';
	file->filename[i++] = 'r';
	file->filename[i] = '\0';
	return (OKAY);
}
