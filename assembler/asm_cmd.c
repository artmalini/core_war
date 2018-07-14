/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:10:31 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:10:34 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			count_cmd_size(t_core *file, t_cmd *c, int l_size)
{
	int		i;
	int 	len;

	i = -1;
	len = 1;
	if (op_tab[file->inst_pos].size == 0)
		l_size = 4;
	if (op_tab[file->inst_pos].size == 1)
		l_size = 2;
	if (op_tab[file->inst_pos].codage != 0)
		len++;
	while (c->args[++i] && c->args[i][0])
	{
			if (c->args[i][0] == REGISTER_CHAR)
				len++;
			else if (c->args[i][0] == DIRECT_CHAR && l_size == 4)
				len = len + 4;
			else if (c->args[i][0] == DIRECT_CHAR && l_size == 2)
				len = len + 2;
			else
				len = len + 2;
	}
	return (len);
}

t_cmd		*add_cmd(t_core *file, char *cmd, char *str_args)
{
	t_cmd	*lst;

	if (!(lst = ft_memalloc(sizeof(t_cmd))))
		ft_error(file, ERROR_MEMORY);
	if (lst)
	{
		lst->nbr_args = NBR_ARGS(file->inst_pos);
        lst->command = cmd ? ft_strdup(cmd) : NULL;
        lst->opcode = op_tab[file->inst_pos].opcode;
		valid_args_main(file, lst, str_args);
        insert_args_lst(file, lst);
		lst->cmd_size = count_cmd_size(file, lst, 0);
		lst->cmd_str_size = file->count_size;
		lst->byte_nbr = file->count_size - lst->cmd_size;
		file->count_size += lst->cmd_size;		
		lst->next = NULL;
	}
//	while (lst && lst->args[i])
//		free(lst->args[i]);
	return (lst);
}

void		push_cmd(t_core *file, t_cmd **lst, char *cmd, char *args)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;		
		tmp->next = add_cmd(file, cmd, args);
	}
	else
		*lst = add_cmd(file, cmd, args);
}
