/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:09:18 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/02 12:09:21 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	wrong_input(int c)
{
	if (c == 0)
		ft_printf("wrong input\n");
	else if (c == 1)
		ft_printf("error\n");
	else if (c == 2)
		ft_printf("wrong file name\n");
	else if (c == 3)
		ft_printf("Open file error\n");
	exit(-1);
}

void		asm_lst_foreach(t_inst *lst, void (*f)())
{
	t_inst		*tmp;

	tmp = lst;
	while (tmp)
	{
		(*f)(tmp->label);
		tmp = tmp->next;
	}
}

void		asm_lst_data_free(t_inst *first)
{
	t_inst	*tmp;

	tmp = first;
	while (first)
	{
		tmp = first;
		first = first->next;
		free(tmp);
	}
}

void		free_label(char *data)
{
	if (data)
	{
		ft_strdel(&data);
		data = NULL;
	}
}

void	free_struct_tcore(t_core *file)
{
	if (file)
	{
		if (file->name)
			ft_strdel(&file->name);
		if (file->comment)
			ft_strdel(&file->comment);
		if (file->filename)
			ft_strdel(&file->filename);
		if (file->inst)
		{
			asm_lst_foreach(file->inst, free_label);
			asm_lst_data_free(file->inst);
		}
	}
}

void	error_file(t_core *file)
{
	ft_printf("error at line %d\n", file->rows);
	free_struct_tcore(file);
	exit(-1);
}
