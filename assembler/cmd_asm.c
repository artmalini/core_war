/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_asm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:10:31 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/05 23:10:34 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_cmd	*add_cmd(char *cmd, char *args, t_core *file)
{
	(void)args;
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		lst->command = cmd ? ft_strdup(cmd) : NULL;
		lst->opcode = op_tab[file->inst_pos].opcode;
		lst->next = NULL;
	}
	//ft_printf("ARGS %s\n", args);
	return (lst);
}

void	push_cmd(char *cmd, char *args, t_core *file, t_cmd **lst)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;		
		tmp->next = add_cmd(cmd, args, file);
	}
	else
		*lst = add_cmd(cmd, args, file);
}