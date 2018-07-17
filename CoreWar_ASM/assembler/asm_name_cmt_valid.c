/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_name_and_cmt_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:02:51 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/02 12:02:56 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			len_check(t_core *file, int type, int len)
{
	if (type == NAME)
	{
		if (len > PROG_NAME_LENGTH)
			return (ft_error_int(file, ERROR_L_NAME));
		if (len < 1)
			return (ft_error_int(file, ERROR_S_NAME));
	}
	if (type == COMMENT)
	{
		if (len > COMMENT_LENGTH)
			return (ft_error_int(file, ERROR_L_CMT));
		if (len < 1)
			return (ft_error_int(file, ERROR_L_CMT));
	}
	return (OKAY);
}

int			parse_header_name(t_core *file, char *str, int i)
{
	int		j;

	j = 0;
	if (str && str[0] != '\"')
		return (ft_error_int(file, ERROR_SYNTAX));
	while (str && str[i])
	{
		if (str[i] == '\"')
			j++;
		i++;
	}
	if (str && str[i - 1] != '\"')
		return (ft_error_int(file, ERROR_SYNTAX));
	return (i);
}

void		rebuild_name_cmt(t_core *file, int len)
{
	char	*tmp;

	if (file->name)
	{
		len = parse_header_name(file, file->name, 0);
		len_check(file, NAME, len - 2);
		tmp = ft_strdup(file->name);
		ft_strdel(&file->name);
		file->name = ft_strsub(tmp, 1, (size_t)(len - 2));
		ft_strdel(&tmp);		
	}
	if (file->comment)
	{
		len = parse_header_name(file, file->comment, 0);
		len_check(file, COMMENT, len - 2);
		tmp = ft_strdup(file->comment);
		ft_strdel(&file->comment);
		file->comment = ft_strsub(tmp, 1, (size_t)(len - 2));
		ft_strdel(&tmp);
	}
}

void		name_cmt(t_core *file, char *str, int type)
{
	size_t	i;

	i = 0;
	while (str && *str && ft_strchr(SPACES_CHARS, *str))
		str++;
	while (str && str[i])
	{
		if (str[i] == '\"')
			file->syntax++;
		if (type == NAME)
			file->name_length++;
		if (type == COMMENT)
			file->cmt_length++;
		i++;
	}
	if (type == NAME)
	{
		file->name = file->name ?
		ft_strjoinstr(file->name, ft_strsub(str, 0, i)) : ft_strsub(str, 0, i);
	}
	if (type == COMMENT)
	{
		file->comment = file->comment ?
		ft_strjoinstr(file->comment, ft_strsub(str, 0, i)) : ft_strsub(str, 0, i);
	}
}

void		name_cmt_valid(t_core *file, char *str)
{
	if (!ft_strncmp(str, NAME_CMD_STRING, 5))
	{
		file->name_nbr++;
		name_cmt(file, str + 5, NAME);
		if (file->name_nbr > 1)
			return(ft_error(file, ERROR_A_NAME));
	}
	else if (!ft_strncmp(str, COMMENT_CMD_STRING, 8))
	{

		file->cmt_nbr++;
		name_cmt(file, str + 8, COMMENT);
		if (file->cmt_nbr > 1)
			return(ft_error(file, ERROR_A_CMT));
	}
	else
	{
		free_struct_tcore(file);
		exit (ERROR);
	}
}
