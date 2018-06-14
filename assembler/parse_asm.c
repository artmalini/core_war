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

char	*ft_strjoinstr(char *str1, char *str2)
{
	char 	*str3;

	if (!str1 || !str2)
		return (NULL);
	str3 = (char *)malloc(sizeof(str3) * ((ft_strlen(str1)) + (ft_strlen(str2))) + 1);
	if (!str3)
		return (NULL);
	*str3 = 0;
	str3 = ft_strcat(ft_strcat(str3, str1), str2);
	free(str1);
	free(str2);
	return (str3);
}

void	len_check(int len, int nb, t_core *file)
{
	if (nb == 1)
	{
		if (len > PROG_NAME_LENGTH)
		{
			ft_printf("ERROR: Name to long\n");
			error_file(file, len);
			exit (ERROR);
		}
		if (len < 1)
		{
			ft_printf("ERROR: Name to short\n");
			error_file(file, len);
			exit (ERROR);
		}
	}
	if (nb == 2)
	{
		if (len > COMMENT_LENGTH)
		{
			ft_printf("ERROR: Comment length to long\n");
			error_file(file, len);
			exit (ERROR);
		}
		if (len < 1)
		{
			ft_printf("ERROR: Comment lengt to short\n");
			error_file(file, len);
			exit (ERROR);
		}
	}
}

int		parse_header_name(char *str, t_core *file)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str && str[0] != '\"')
	{
		ft_printf("ERROR: in file wrong syntax\n");
		free_struct_tcore(file);
		exit (ERROR);
	}
	while (str && str[i])
	{
		if (str[i] == '\"')
			j++;
		i++;
	}
	if (str[i - 1] != '\"')
	{
		ft_printf("ERROR: in file wrong syntax\n");
		free_struct_tcore(file);
		exit (ERROR);
	}
	//ft_printf("		@@@@len|%d| quoters|%d|\n", i, j);
	return (i);
}

void	rebuild_name_cmt(t_core *file)
{
	int		len;
	char	*tmp;

	tmp = NULL;
	len = 0;
	if (file->name)
	{
		len = parse_header_name(file->name, file);
		len_check(len - 2, 1, file);
		tmp = ft_strdup(file->name);
		ft_strdel(&file->name);
		file->name = ft_strsub(tmp, 1, (len - 2));
		ft_strdel(&tmp);		
	}
	if (file->comment)
	{
		len = parse_header_name(file->comment, file);
		len_check(len - 2, 2, file);
		tmp = ft_strdup(file->comment);
		ft_strdel(&file->comment);
		file->comment = ft_strsub(tmp, 1, (len - 2));
		ft_strdel(&tmp);
	}
	//ft_printf("len|%d|\n", len);
}

void	name_cmt(char *str, int nb, t_core *file)
{
	int		i;

	i = 0;
	//ft_printf("STR |%s|\n", str);
	while (str && *str && ft_isspace(*str))
		str++;
	while (str && str[i])
	{
		if (str[i] == '\"')
			file->syntax++;
		if (nb == 1)
			file->name_length++;
		if (nb == 2)
			file->cmt_length++;
		i++;
	}
	if (nb == 1)
	{
		file->name = file->name ? ft_strjoinstr(file->name, ft_strsub(str, 0, i)) : ft_strsub(str, 0, i);
	}
	if (nb == 2)
	{
		file->comment = file->comment ? ft_strjoinstr(file->comment, ft_strsub(str, 0, i)) : ft_strsub(str, 0, i);
	}
}

void	name_cmt_valid(char *str, t_core *file)
{
	if (!ft_strncmp(str, NAME_CMD_STRING, 5))
	{
		//write_name_or_cmt(str, 1, file);
		file->name_nbr++;
		name_cmt(str + 5, 1, file);
		if (file->name_nbr > 1)
		{
			ft_printf("ERROR: in file  to many .name arguments\n");
			free_struct_tcore(file);
			exit (ERROR);
		}
	}
	else if (!ft_strncmp(str, COMMENT_CMD_STRING, 8))
	{
		
		//write_name_or_cmt(str, 2, file);
		file->cmt_nbr++;
		name_cmt(str + 8, 2, file);
		if (file->cmt_nbr > 1)
		{
			ft_printf("ERROR: in file to many .comment arguments\n");
			free_struct_tcore(file);
			exit (ERROR);
		}
	}
	else
	{
		ft_printf("ERROR: %s at line %d\n", file->filename, file->rows);
		free_struct_tcore(file);
		exit (ERROR);
	}
}

void		read_init_line(char *line, t_core *file)
{
	char	*str;
	int		nb;

	str = line;
	nb = 0;
	while (str && *str && ft_isspace(*str))
	 	str++;
	if (str && str[0] == '.')
	{
		file->point_nbr++;
		name_cmt_valid(str, file);
	}
	else if (str && (str[0] == COMMENT_CHAR
			|| str[0] == COMMENT_CHAR2 || *str == '\0'))
	{
		ft_strdel(&line);
		return ;
	}
	else
	{
		if ((file->name_nbr == 0 || file->name_nbr == 1) && file->cmt_nbr == 0)
			nb = 1;
		else
			nb = 2;
		name_cmt(str, nb, file);
	}
	if (file->syntax == 4)
		file->flag = 1;//exit maybe all find
	ft_strdel(&line);
}

void	parse_header(int fd, t_core *file)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) && !file->flag)
	{
		file->rows++;
		if (line_has_val(line))
			read_init_line(line, file);
		else
			ft_strdel(&line);
	}
	ft_strdel(&line);
	if (file->syntax != 4)
	{
		ft_printf("ERROR: wrong syntax %s |%d|\n", file->filename, file->syntax);
		//free_struct_tcore(file);
		exit(ERROR);
	}
	rebuild_name_cmt(file);
}

void	read_line(char *line, t_core *file)
{
	char	*str;

	str = line;
	while (str && *str && ft_isspace(*str))
	 	str++;
	if (str && (str[0] == COMMENT_CHAR
			|| str[0] == COMMENT_CHAR2))
	{
		ft_strdel(&line);
		return ;
	}
	else
		line_handler(str, file);
	//ft_printf("read_line |%s|\n", str);
	ft_strdel(&line);
}

void	parse_file(char *arg, t_core *file)
{
	char	*line;
	int		fd;

	line = NULL;
	if (!(fd = open(arg, O_RDONLY)))
		wrong_input(3);
	parse_header(fd, file);
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
