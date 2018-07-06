/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:04:40 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:04:42 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		read_init_line(char *line, t_core *file, int nb, char *arg)
{
	char	*str;

	str = line;
	while (str && *str && ft_strchr(SPACES_CHARS, *str))
	 	str++;
	if (str && str[0] == '.')
	{
		file->point_nbr++;
		name_cmt_valid(str, file, arg);
	}
	else if (str && (str[0] == COMMENT_CHAR
			|| str[0] == COMMENT_CHAR2 || *str == '\0'))
	{
		ft_strdel(&line);
		return ;
	}
	else
	{
		nb = (file->name_nbr == 1 && file->cmt_nbr == 0)? 1 : 2;
		name_cmt(str, nb, file);
	}
	if (file->syntax == 4)
		file->flag = 1;//exit maybe all find
	ft_strdel(&line);
}

void	parse_header(int fd, char *arg, t_core *file)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) && !file->flag)
	{
		file->rows++;
		if (line_has_val(line))
			read_init_line(line, file, 0, arg);
		else
			ft_strdel(&line);
	}
	ft_strdel(&line);
	if (file->syntax != 4)
		error_file(file, arg, 4);
	rebuild_name_cmt(file, arg);
	//len_check(ft_strlen(file->name), 1, file);
	//len_check(ft_strlen(file->comment), 2, file);
}

void	read_line(char *line, char *arg, t_core *file)
{
	char	*str;

	str = line;
	while (str && *str && ft_strchr(SPACES_CHARS, *str))
	 	str++;
	if (str && (str[0] == COMMENT_CHAR
			|| str[0] == COMMENT_CHAR2))
	{
		ft_strdel(&line);
		return ;
	}
	else
		line_handler(str, arg, file);
	//ft_printf("read_line |%s|\n", str);
	ft_strdel(&line);
}

void	parse_file(char *arg, t_core *file)
{
	char	*line;
	int		fd;

	line = NULL;
	if (!(fd = open(arg, O_RDONLY)))
		error_file(file, arg, 4);
	parse_header(fd, arg, file);
	while (get_next_line(fd, &line))
	{
		file->rows++;
		if (line_has_val(line))
			read_line(line, arg, file);
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
		error_file(file, arg, 2);
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
