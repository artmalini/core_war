/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_and_cmt_valid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:02:51 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/02 12:02:56 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	len_check(int len, int nb, t_core *file)
{
	if (nb == 1)
	{
		if (len > PROG_NAME_LENGTH)
		{
			ft_printf("ERROR: Name to long\n");
			error_file(file);
		}
	}
	if (nb == 2)
	{
		if (len > COMMENT_LENGTH)
		{
			ft_printf("ERROR: Comment length to long\n");
			error_file(file);
		}
	}
}

void	name_and_cmt_valid(char *line, int nb, t_core *file)
{
	int		count;
	int		len;

	count = 0;
	len = 0;
	//line += nb == 1 ? 6 : 9;
	while (*line && *line != '\"')
		line++;	
	if (*line == '\"')
	{
		count++;
		line++;
	}
	while (*line && *line != '\"')
	{
		len++;
		if (!ft_strchr(HEADER_CHARS, *line))
		{
			ft_printf("### |%c|", *line);
			error_file(file);
		}
		len_check(len, nb, file);
		line++;
	}
	if (*line == '\"')
		count++;
	if (count != 2)
		error_file(file);
}

void	write_name_or_cmt(char *line, int nb, t_core *file)
{
	int		i;

	i = 0;
	while (*line && *line != '\"')
		line++;
	line++;
	while (line[i] && line[i] != '\"')
		i++;
	if (nb == 1)
	{
		file->name = ft_strsub(line, 0, i);
		ft_printf("name_and_cmt_valid name	|%s|\n", line);
	}
	if (nb == 2)
	{
		file->comment = ft_strsub(line, 0, i);
		ft_printf("name_and_cmt_valid comment	|%s|\n", line);
	}
}

void	name_and_cmt(char *line, t_core *file)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, 5))
	{
		name_and_cmt_valid(line, 1, file);
		write_name_or_cmt(line, 1, file);
	}
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
	{
		name_and_cmt_valid(line, 2, file);
		write_name_or_cmt(line, 2, file);
	}
	else
	{
		free_struct_tcore(file);
		ft_printf("ERROR: After decimal symbol at line %d\n", file->rows);
		exit (-1);
	}
}
