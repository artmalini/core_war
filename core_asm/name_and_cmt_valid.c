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

#include "../includes/core.h"

void	len_check(int len, int nb, t_core *file)
{
	if (nb == 1)
	{
		if (len > PROG_NAME_LENGTH)
		{
			ft_printf("Name to long\n");
			error_file(file);
		}
	}
	if (nb == 2)
	{
		if (len > COMMENT_LENGTH)
		{
			ft_printf("Comment length to long\n");
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

void	name_and_cmt(char *line, t_core *file)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		name_and_cmt_valid(line, 1, file);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		name_and_cmt_valid(line, 2, file);
	else
	{
		free_struct_tcore(file);
		ft_printf("error, after decimal symbol at line %d\n", file->rows);
		exit (-1);
	}
}
