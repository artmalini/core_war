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
	file->inst = NULL;
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




t_inst		*add_label(char *str)
{
	t_inst	*lst;

	lst = NULL;
	lst = (t_inst *)malloc(sizeof(t_inst));
	if (lst)
	{
		lst->label = str ? ft_strdup(str) : NULL;
		lst->next = NULL;
	}
	return (lst);
}

void	push_laybel(char *str, t_inst **lst)
{
	t_inst	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add_label(str);
	}
	else
	{
		*lst = add_label(str);
	}
}

void	line_handler(char *line, t_core *file)
{
	int		i;
	int		flag;
	char	*str;
	char	*lowstr;

	i = 0;
	flag = 0;
	str = line;
	lowstr = NULL;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != ':'))
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
			error_file(file);
		i++;
	}
	if (str[i] == ':')
	{
		lowstr = ft_strsub(str, 0, i);
		push_laybel(lowstr, &file->inst);

		ft_printf("@@@@ (|%s|)\n", lowstr);
		ft_strdel(&lowstr);
	}

	//ft_printf("@@@@ |%s| %d\n", str + i, i);
	str += i;
	ft_printf("line_handler |%s| str |%s|\n", line, str);
	return ;
}

void	read_line(char *line, t_core *file)
{
	if (line[0] == '.')
	{
		name_and_cmt(line, file);
	}
	else if (line[0] == COMMENT_CHAR || ft_strchr(line, COMMENT_CHAR))
	{
		ft_strdel(&line);
		return ;
	}
	else
		line_handler(line, file);
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





void	label_debug(t_core *file)
{
		t_inst	*inst;

		inst = file->inst;
		while (inst)
		{
			ft_printf("^^ %s\n", inst->label);
			inst = inst->next;
		}
}

int		main(int argc, char **argv)
{
	t_core	file;

	if (argc == 2)
	{
		init_struct(&file);
		if (!parse_filename(argv[1], &file))
			wrong_input(1);
		parse_file(argv[1], &file);




		label_debug(&file);
		ft_printf("ok rows %d\n", file.rows);

		free_struct_tcore(&file);
		//system("leaks asm");
	}
	else
		wrong_input(0);
	return (0);
}
