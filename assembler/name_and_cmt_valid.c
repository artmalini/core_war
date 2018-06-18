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

int		len_check(int len, int nb, t_core *file, char *arg)
{
	if (nb == 1)
	{
		if (len > PROG_NAME_LENGTH)
			error_file(file, arg, 8);
		if (len < 1)
			error_file(file, arg, 9);
	}
	if (nb == 2)
	{
		if (len > COMMENT_LENGTH)
			error_file(file, arg, 10);
		if (len < 1)
			error_file(file, arg, 11);
	}
	return (0);
}

int		parse_header_name(char *str, t_core *file, char *arg)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str && str[0] != '\"')
		error_file(file, arg, 5);
	while (str && str[i])
	{
		if (str[i] == '\"')
			j++;
		i++;
	}
	if (str[i - 1] != '\"')
		error_file(file, arg, 5);
	//ft_printf("		@@@@len|%d| quoters|%d|\n", i, j);
	return (i);
}

void	rebuild_name_cmt(t_core *file, char *arg)
{
	int		len;
	char	*tmp;

	tmp = NULL;
	len = 0;
	if (file->name)
	{
		len = parse_header_name(file->name, file, arg);
		len_check(len - 2, 1, file, arg);
		tmp = ft_strdup(file->name);
		ft_strdel(&file->name);
		file->name = ft_strsub(tmp, 1, (len - 2));
		ft_strdel(&tmp);		
	}
	if (file->comment)
	{
		len = parse_header_name(file->comment, file, arg);
		len_check(len - 2, 2, file, arg);
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
		file->name = file->name ?
		ft_strjoinstr(file->name, ft_strsub(str, 0, i)) : ft_strsub(str, 0, i);
	}
	if (nb == 2)
	{
		file->comment = file->comment ?
		ft_strjoinstr(file->comment, ft_strsub(str, 0, i)) : ft_strsub(str, 0, i);
	}
}

void	name_cmt_valid(char *str, t_core *file, char *arg)
{
	if (!ft_strncmp(str, NAME_CMD_STRING, 5))
	{
		//write_name_or_cmt(str, 1, file);
		file->name_nbr++;
		name_cmt(str + 5, 1, file);
		if (file->name_nbr > 1)
			error_file(file, arg, 6);
	}
	else if (!ft_strncmp(str, COMMENT_CMD_STRING, 8))
	{
		
		//write_name_or_cmt(str, 2, file);
		file->cmt_nbr++;
		name_cmt(str + 8, 2, file);
		if (file->cmt_nbr > 1)
			error_file(file, arg, 7);
	}
	else
	{
		//ft_printf("ERROR: %s at line %d\n", file->filename, file->rows);
		free_struct_tcore(file);
		exit (ERROR);
	}
}
