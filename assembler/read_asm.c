/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:01:57 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:01:58 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	read_line(char *line, t_core *file)
{
	char	*str;

	str = line;
	while (*str && (*str == ' ' || *str == '\t'))
	 	str++;
	if (str[0] == '.')
	{
		name_and_cmt(str, file);
	}
	else if (str[0] == COMMENT_CHAR
		|| str[0] == COMMENT_CHAR2)
	{
		ft_strdel(&line);
		return ;
	}
	else
		line_handler(str, file);
	//ft_printf("read_line |%s|\n", str);
	ft_strdel(&line);
}