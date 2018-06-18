/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:35:02 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:35:05 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		line_has_val(char *line)
{
	while (line && *line)
	{
		if (*line != '\t' && *line != ' ')
			return (1);
		line++;
	}
	return (0);	
}

int		check_command(char	*lowstr, t_core *file)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (!ft_strcmp(op_tab[i].name, lowstr))
		{
			file->inst_pos = i;
			return (1);
		}
	}
	return (0);
}

char		*line_finalize(char **str, char *lowstr, int *i, t_core *file)
{
	if (*i == 0)//label exist, if i == 0 should be error!
		error_cor(file, 2);
	lowstr = ft_strsub(*str, 0, *i);
	push_laybel(lowstr, &file->inst, file);
		ft_printf("\n---> Finded LABEL: [%s]\n", lowstr);
	ft_strdel(&lowstr);
	while (**str && ft_strchr(LABEL_CHARS, **str) && **str != ':')
		(*str)++;
	if (**str == ':')
		(*str)++;//!!!!!for :
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
	if (!(**str))
		return (NULL);
	*i = 0;
		ft_printf("** Analyze String: [%s]\n", *str);
	while ((*str)[*i] && ((*str)[*i] != ' ' && (*str)[*i] != '\t'))
	{
		if (!ft_strchr(LABEL_CHARS, (*str)[*i]))
		{
			ft_printf("!! Line_handler:	ERROR\n");
			error_cor(file, 1);
		}
		(*i)++;
	}
	lowstr = ft_strsub(*(str), 0, *i);
	return (lowstr);
}

void	line_handler(char *line, char *arg, t_core *file)
{
	int		i;
	char	*str;
	char	*lowstr;

	i = 0;
	str = line;
	lowstr = NULL;
	while (str[i] && str[i] != ':' && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] == ':')
	{
		if (!(lowstr = line_finalize(&str, lowstr, &i, file)))
			return ;
	}	
	else
		lowstr = ft_strsub(str, 0, i);
	if (check_command(lowstr, file))
	{
		ft_printf("** Check_commands: [%s]  |%s|%d\n", lowstr, str + (ft_strlen(lowstr) + 1), i);
		if (!file->inst)//!!!!!!!!!  IF LABEL DOES NOT EXIST
			push_laybel(NULL, &file->inst, file);
		push_cmd(lowstr, str + (ft_strlen(lowstr) + 1), file, &file->inst->cmd);
	}
	else
		error_file(file, arg, 0);//wrong command
	ft_strdel(&lowstr);
}
