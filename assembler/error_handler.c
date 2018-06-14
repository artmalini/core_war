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

/*void	wrong_input_ext(int c, char *arg, t_core *file)
{
	if (c == 12)
		ft_printf("ERROR: Label must be at least one characte\n");
}*/

void	wrong_input(int c, char *arg, t_core *file)
{
	if (c == 0)
		ft_printf("ERROR: %s at line %d\n", arg, file->rows);
	else if (c == 1)
		ft_printf("ERROR: wrong input arguments\n");
	else if (c == 2)
		ft_printf("ERROR: wrong input\n");
	else if (c == 3)
		ft_printf("ERROR: %s wrong file name\n", arg);
	else if (c == 4)
		ft_printf("ERROR: Open file %s error\n", arg);
	else if (c == 5)
		ft_printf("ERROR: %s wrong_syntax\n", arg);
	else if (c == 6)
		ft_printf("ERROR: %s to many .name arguments\n", arg);
	else if (c == 7)
		ft_printf("ERROR: %s to many .comment arguments\n", arg);
	else if (c == 8)
		ft_printf("ERROR: %s Name to long\n", arg);
	else if (c == 9)
		ft_printf("ERROR: %s Name to short\n", arg);
	else if (c == 10)
		ft_printf("ERROR: %s Comment length to long\n", arg);
	else if (c == 11)
		ft_printf("ERROR: %s Comment length to short\n", arg);
	//wrong_input_ext(c, arg, file);
}

void	error_file(t_core *file, char *arg, int nbr_char)
{
	//ft_printf("error_file [line] - [%d] nbr_char|%d|\n", file->rows, nbr_char);
	wrong_input(nbr_char, arg, file);
	free_struct_tcore(file);
	exit(ERROR);
}

void	error_cor(t_core *file, int nbr_char)
{
	if (nbr_char == 0)
		ft_printf("ERROR: more then one identical labels\n");
	else if (nbr_char == 1)
		ft_printf("ERROR: syntax error\n");
	else if (nbr_char == 2)
		ft_printf("ERROR: Label must be at least one characte\n");
	free_struct_tcore(file);
	exit(ERROR);
}

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
	while (inst)
	{
		ft_strdel(&inst->label);
		inst = inst->next;
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
		if (file->inst)
		{
			inst_data_free(file->inst);
			inst_free(file->inst);
			if (file->inst->cmd)
			{
				cmd_free(file->inst->cmd);
				cmd_lst_free(file->inst->cmd);
			}
		}
		//ft_memdel((void**)&file);
	}
}



