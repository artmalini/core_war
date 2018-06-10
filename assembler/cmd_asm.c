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

void	free_mas(char **mas)
{
	int i;

	i = -1;
	while (mas[++i] != NULL)
		free(mas[i]);
	free(mas);
}

char	*insert_cmd_string(char *args)
{
	int		i;
	int		j;
	//int		flag;
	char	*str;

	i = 0;
	j = 0;
	//flag = 0;
	if (!(str = (char *)malloc(sizeof(str) * (ft_strlen(args) + 1))))
		return (NULL);
	while (args[i])
	{
		while (args[i] && (args[i] != ' ' && args[i] != '\t' && args[i] != ','))
		{
			str[j++] = args[i++];
		}
		while (args[i] && (args[i] == ' ' || args[i] == '\t' || args[i] == ','))
		{
			i++;
		}
		if ((args[i] != '\n' && args[i]))
		{
			ft_printf("ok |%c|\n", args[i]);
			str[j++] = ' ';
		}
		//if (args[i])
		//	i++;
	}
	str[j] = '\0';
	ft_printf("INSERT STR|%s|\n", str);
	return (str);
}

int		count_cmd_size(char **mas, t_core *file, t_cmd *lst)
{
	int		l_size;
	int		len;
	int		i;
	//int		j;

	//ft_printf("ARGS count_cmd_size|%s|\n", args);
	len = 1;
	l_size = 0;
	i = -1;
	if (op_tab[file->inst_pos].size == 0)
		l_size = 4;
	if (op_tab[file->inst_pos].size == 1)
		l_size = 2;
	if (op_tab[file->inst_pos].codage != 0)
		len++;
	while (mas[++i] && mas[i][0])
	{
			if (mas[i][0] == 'r')
				len++;
			else if (mas[i][0] == '%' && l_size == 4)
				len = len + 4;
			else if (mas[i][0] == '%' && l_size == 2)
				len = len + 2;
			else
				len = len + 2;
			if(mas[i][0] == 'r' && mas[i][1] == ':')
				lst->byte_method_nbr = len;
			//ft_printf("mas[i][j]%s| %d\n", mas[i], l_size);
		
	}
	ft_printf("				LEN|%d\n", len);
	return (len);
}

t_cmd	*add_cmd(char *cmd, char *args, t_core *file)
{
	t_cmd	*lst;
	char	**mas;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	mas = NULL;
	if (lst)
	{
		//should be validation here for args
		//error_file(file)
		valid_args(args, file);
		//adn return fresh args string 	
		//save this fresh string in to lst
		lst->command = cmd ? ft_strdup(cmd) : NULL;
		lst->opcode = op_tab[file->inst_pos].opcode;
		//insert to count_cmd_size this fresh string 	done
		//insert_cmd_string(args); 						done
		lst->str = args ? insert_cmd_string(args) : NULL;
		mas = ft_strsplit(lst->str, ' ');
		lst->arg1 = op_tab[file->inst_pos].nbr_args > 0 ? ft_strdup(mas[0]) : NULL;
		lst->arg2 = op_tab[file->inst_pos].nbr_args > 1 ? ft_strdup(mas[1]) : NULL;
		lst->arg3 = op_tab[file->inst_pos].nbr_args > 2 ? ft_strdup(mas[2]) : NULL;
		lst->cmd_size = count_cmd_size(mas, file, lst);

		//lst->byte_method_nbr = lst->cmd_size;
		file->count_size += lst->cmd_size;
		
		file->count_pos += file->count_size;
		lst->byte_nbr = file->count_size - lst->cmd_size;
		lst->next = NULL;
	}
	ft_printf("---> Finded lst->str:  [%s]		|%s| |%s| |%s| lst->cmd_size|%d|\n\n", lst->str, lst->arg1, lst->arg2, lst->arg3, lst->cmd_size);
	ft_printf(" lst->byte_method_nbr|%d|\n", lst->byte_method_nbr);
	free_mas(mas);
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