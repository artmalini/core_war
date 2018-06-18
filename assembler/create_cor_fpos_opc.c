/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor_fpos_opc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:11:08 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:11:11 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_pos_cmd(char *str, t_core *file, t_inst *inst, int cmd_size)
{
	int		i;
	t_inst	*tmp;

	tmp = inst;
	i = -1;
	while (++i < 2)
	{
		while (tmp)
		{
			if (tmp->label)
			{
				if (!ft_strcmp(tmp->label, str))
					return (cmd_size);			
			}
			tmp = tmp->next;
		}
		tmp = inst;
	}
	if (i == 1)
		error_cor(file, 0);
	return (0);
}

int		get_binary_code(char c)
{
	//ft_printf("get_binary_code %c\n", c);
	if (c == 'r')
		return (1);
	else if (c == '%')
		return (10);
	else
		return (11);
}

int		result_opcode(char c, int code, int get_bin)
{
	int		res;
	int		binary;

	res = 0;
	binary = get_binary_code(c);
	res = get_bin + (binary / 10 * code) + (binary % 10 * code / 2);
	//ft_printf("RES %d\n", res);
	return (res);
}

int		count_opcode(char *str)//should be better validation for *str
{
	int		get_bin;
	int		code;

	get_bin = 0;
	code = 128;
	if (!str)//////
		return (0);
	while (str && *str && (*str != '#' && *str != ';'))
	{
		if ((*str == 'r') || (*str == '%' || *str == ':') ||
			(*str >= '0' && *str <= '9'))
		{
			get_bin = result_opcode(*str, code, get_bin);
			while (*str && (*str != ' '))
				str++;
			code /= 4;
		}
		if (*str)
			str++;			
	}
	return (get_bin);
}