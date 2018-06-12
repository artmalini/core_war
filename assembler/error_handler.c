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

/*void		asm_lst_foreach(t_inst *lst, void (*f)())
{
	t_inst		*tmp;

	tmp = lst;
	while (tmp)
	{
		(*f)(tmp->label);
		tmp = tmp->next;
	}
}

void		free_label(char *data)
{
	if (data)
	{
		ft_strdel(&data);
		data = NULL;
	}
}*/





void	cmd_free(t_cmd *cmd)
{
	while (cmd)
	{
		ft_strdel(&cmd->command);
		ft_strdel(&cmd->str);
		ft_strdel(&cmd->arg1);
		ft_strdel(&cmd->arg2);
		ft_strdel(&cmd->arg3);
		cmd = cmd->next;
	}
}

void	cmd_lst_free(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	inst_data_free(t_inst *inst)
{
	//t_inst	*tmp;

	//tmp = inst;
	while (inst)
	{
		ft_strdel(&inst->label);
		//cmd_free(inst->cmd);
		inst = inst->next;
		//free(tmp);
	}
}

void		inst_free(t_inst *first)
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
		if (file->inst->cmd)
		{
			cmd_free(file->inst->cmd);
			cmd_lst_free(file->inst->cmd);
		}
		if (file->inst)
		{
			inst_data_free(file->inst);
			inst_free(file->inst);
		}
		// if (file->inst)
		// {
		// 	asm_lst_foreach(file->inst, free_label);
		// 	asm_lst_data_free(file->inst);
		// }
		//ft_memdel((void**)&file);
	}
}

void	error_file(t_core *file, int nbr_char)
{
	ft_printf("ERROR: At [line]/[Byte_nbr] - [%d]/[%d]\n", file->rows, nbr_char);
	free_struct_tcore(file);
	exit(ERROR);
}
