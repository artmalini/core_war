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

// void		valid_args(char *args, t_core *file)
// {
// 	if (op_tab[file->inst_pos].nbr_args == 1)
// }

int		count_cmd_size(char *args, t_core *file)
{
	int		l_size;
	int		len;

	len = 1;
	l_size = 0;
	if (op_tab[file->inst_pos].size == 0)
		l_size = 4;
	if (op_tab[file->inst_pos].size == 1)
		l_size = 2;
	if (op_tab[file->inst_pos].codage != 0)
		len++;
	while (*args)
	{
		if (*args == 'r')
			len++;
		else if (*args == '%' && l_size == 4)
			len = len + 4;
		else if (*args == '%' && l_size == 2)
			len = len + 2;
		args++;
	}
	return (len);
}

t_cmd	*add_cmd(char *cmd, char *args, t_core *file)
{
	(void)args;
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		//should be validation here for args
		//error_file(file)
		//valid_args(args, file);
		//adn return fresh args string 	
		//save this fresh string in to lst
		lst->command = cmd ? ft_strdup(cmd) : NULL;
		lst->opcode = op_tab[file->inst_pos].opcode;
		//insert to count_cmd_size this fresh string
		lst->cmd_size = count_cmd_size(args, file);
		file->count_size += lst->cmd_size;
		lst->next = NULL;
	}
	ft_printf("ARGS %s\n", args);
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