/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:55:49 by amakhiny          #+#    #+#             */
/*   Updated: 2018/05/30 13:55:58 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	init_struct(t_core *file)
{
	file->name = NULL;
	file->comment = NULL;
	file->filename = NULL;
	file->rows = 0;
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

int		line_has_val(char *line)
{
	while (*line)
	{
		if (*line != '\t' || *line != ' ')
			return (1);
		line++;
	}
	return (0);
}



void	read_line(char *line, t_core *file)
{
	if (line[0] == '.')
	{
		name_and_cmt(line, file);
	}
	ft_printf("read_line |%s|\n", line);
	ft_strdel(&line);
}

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

// void	tab_builder(void)
// {
// 	ft_printf("%s\n", op_tab[1].name);
// }

int		main(int argc, char **argv)
{
	t_core	file;

	if (argc == 2)
	{
		init_struct(&file);
		if (!parse_filename(argv[1], &file))
			wrong_input(1);
		parse_file(argv[1], &file);


		//tab_builder(); //not need
		ft_printf("ok rows %d\n", file.rows);

		free_struct_tcore(&file);
		//system("leaks asm");
	}
	else
		wrong_input(0);
	return (0);
}
