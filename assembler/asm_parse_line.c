/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:35:02 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:35:05 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			line_has_val(char *line)
{
	while (line && *line)
	{
		if (*line != '\t' && *line != ' ')
			return (OKAY);
		line++;
	}
	return (ERROR);
}

int			check_command(t_core *file, char *lowstr)
{
	int		i;

	i = -1;
	if (!file || !lowstr)
		return (ft_error_int(file, ERROR_FT_ARG));
	file->error->current_cmd = lowstr;
	while (++i < 16)
	{
		if (!ft_strcmp(g_op_tab[i].name, lowstr))
		{
			file->inst_pos = i;
			return (OKAY);
		}
	}
	return (ERROR);
}

char		*line_finalize(t_core *file, char **str, char *lowstr, int *i)
{
	if (*i == 0)
		ft_error(file, ERROR_LABEL);
	lowstr = ft_strsub(*str, 0, (size_t)*i);
	push_laybel(file, &file->inst, lowstr);
	ft_strdel(&lowstr);
	while (**str && ft_strchr(LABEL_CHARS, **str) && **str != ':')
		(*str)++;
	if (**str == ':')
		(*str)++;
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
	if (!(**str))
		return (NULL);
	*i = 0;
	while ((*str)[*i] && ((*str)[*i] != ' ' && (*str)[*i] != '\t'))
	{
		if (!ft_strchr(LABEL_CHARS, (*str)[*i]))
			ft_error(file, ERROR_LABEL);
		(*i)++;
	}
	lowstr = ft_strsub(*(str), 0, (size_t)*i);
	return (lowstr);
}

void		line_handler(t_core *file, char *line, char *lowstr)
{
	int		i;
	char	*str;

	i = 0;
	str = line;
	file->error->current_cmd = lowstr;
	while (str[i] && str[i] != ':' && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] == ':')
	{
		if (!(lowstr = line_finalize(file, &str, lowstr, &i)))
			return ;
	}
	else
		lowstr = ft_strsub(str, 0, (size_t)i);
	if (check_command(file, lowstr) == OKAY)
	{
		if (!file->inst)
			push_laybel(file, &file->inst, NULL);
		push_cmd(file, &file->inst->cmd, lowstr, str + (ft_strlen(lowstr) + 1));
	}
	else
		return (ft_error(file, ERROR_CMD));
	ft_strdel(&lowstr);
}
