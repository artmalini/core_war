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

void	wrong_input(int c)
{
	if (c == 0)
		ft_printf("wrong input\n");
	else if (c == 1)
		ft_printf("error\n");
	else if (c == 2)
		ft_printf("wrong file name\n");
	exit(-1);
}

void	init_struct(t_core *file)
{
	file->filename = NULL;
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

int		main(int argc, char **argv)
{
	t_core	file;

	if (argc == 2)
	{
		init_struct(&file);
		if (!parse_filename(argv[1], &file))
			wrong_input(1);
		ft_printf("ok %d", 1);
	}
	else
		wrong_input(0);
	return (0);
}
