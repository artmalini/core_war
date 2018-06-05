/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:55:49 by amakhiny          #+#    #+#             */
/*   Updated: 2018/05/30 13:55:58 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	init_struct(t_core *file)
{
	file->name = NULL;
	file->comment = NULL;
	file->filename = NULL;
	file->rows = 0;
	file->inst_pos = 0;
	file->inst = NULL;
}

int		parse_filename(char	*arg, t_core *file)
{
	int		len;
	int		i;
	int		l;

	len = ft_strlen(arg);
	i = -1;
	if ((arg[len - 1] != 's' || arg[len - 2] != '.') || len < 3)
		wrong_input(2);
	l = len - 1;
	file->filename = (char*)malloc(sizeof(t_core) * (len + 4));
	while (++i < l)
		file->filename[i] = arg[i];
	file->filename[i++] = 'c';
	file->filename[i++] = 'o';
	file->filename[i++] = 'r';
	file->filename[i] = '\0';
	//ft_printf("filename %s\n",file->filename);
	return (1);
}

int		line_has_val(char *line)
{
	while (*line)
	{
		if (*line != '\t' || *line != ' ')
			return (1);
		line++;
	}
	return (0);	
}




t_inst		*add_label(char *str)
{
	t_inst	*lst;

	lst = NULL;
	lst = (t_inst *)malloc(sizeof(t_inst));
	if (lst)
	{
		lst->label = str ? ft_strdup(str) : NULL;
		lst->cmd = NULL;
		lst->next = NULL;
	}
	return (lst);
}

void	push_laybel(char *str, t_inst **lst)
{
	t_inst	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add_label(str);
	}
	else
	{
		*lst = add_label(str);
	}
}



t_cmd	*add_cmd(char *cmd, char *args, t_core *file)
{
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


int		check_command(char	*lowstr, t_core *file)
{
	int		i;

	i = -1;
	//ft_printf("93 check_command check_command |%s|\n", lowstr);
	while (++i < 16)
	{
		if (!ft_strcmp(op_tab[i].name, lowstr))
		{
			file->inst_pos = i;
			return (1);
		}
	}
	return (0);
}


void	line_handler(char *line, t_core *file)
{
	int		i;
	int		flag;
	char	*str;
	char	*lowstr;

	i = 0;
	flag = 0;
	str = line;
	lowstr = NULL;
	//while (*str && (*str == ' ' || *str == '\t'))
	//	str++;
	while (str[i] && str[i] != ':' && ft_strchr(LABEL_CHARS, str[i]))
	{		
		i++;
	}
	if (str[i] == ':')//label exist, if i == 0 should be error!
	{
		lowstr = ft_strsub(str, 0, i);
		push_laybel(lowstr, &file->inst);

		ft_printf("135 line_handler (|%s|)\n", lowstr);
		ft_strdel(&lowstr);
		flag = 1;
	}
	//if (!ft_strchr(LABEL_CHARS, str[i]))
	//		error_file(file);	
	if (flag) //label exist  l2:
	{
		while (*str && ft_strchr(LABEL_CHARS, *str) && *str != ':')
			str++;
		str++;//!!!!!for :
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		i = 0;
		ft_printf("	149 STR|%s|\n", str);
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
			{
				ft_printf("154 line_handler ERROR\n");
				error_file(file);
			}
			i++;
		}
		lowstr = ft_strsub(str, 0, i);
	}
	else
	{
		lowstr = ft_strsub(str, 0, i);
	}
	if (check_command(lowstr, file))
	{
		ft_printf("167 line_handler check_command |%s|	|%s|\n", lowstr, str + (ft_strlen(lowstr) + 1));
		if (!file->inst)//!!!!!!!!!  IF LABEL DOES NOT EXIST
			push_laybel(NULL, &file->inst);
		push_cmd(lowstr, str + (ft_strlen(lowstr) + 1), file, &file->inst->cmd);
	}
	else
	{//wrong command
		ft_printf("171 line_handler ERROR\n");
		error_file(file);
	}


	ft_strdel(&lowstr);
	//ft_printf("@@@@ |%s| %d\n", str + i, i);
	//str += i;
	//ft_printf("line_handler|%s| 		str|%s|\n", line, str);	
}

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

void	parse_file(char *arg, t_core *file)
{
	char	*line;
	int		fd;

	if (!(fd = open(arg, O_RDONLY)))
		wrong_input(3);
	while (get_next_line(fd, &line))
	{
		file->rows++;
		if (line_has_val(line))
			read_line(line, file);
		else
			ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
}





void	label_debug(t_core *file)
{
		t_inst	*inst;

		inst = file->inst;
		while (inst)
		{
			ft_printf("268 label_debug |%s|\n", inst->label);
			inst = inst->next;
		}
}

void	cmd_debug(t_inst *inst)
{
	t_cmd	*comm;

	while (inst)
	{
		ft_printf("279 cmd_debug label|%s|\n", inst->label);
		comm = inst->cmd;
		while (comm)
		{
			ft_printf("283 md_debug 	command|%s| opcode|%d|\n", comm->command, comm->opcode);
			comm = comm->next;
		}
		inst = inst->next;
	}
}

int		main(int argc, char **argv)
{
	t_core	file;

	if (argc == 2)
	{
		init_struct(&file);
		if (!parse_filename(argv[1], &file))
			wrong_input(1);
		parse_file(argv[1], &file);



		ft_printf("\n\n");
		label_debug(&file);//LABEL DEBUG
		ft_printf("\n");
		cmd_debug(file.inst);///COMMAND debug		
		ft_printf("\n");
		ft_printf("ok rows %d\n", file.rows);

		free_struct_tcore(&file);
		//system("leaks asm");
	}
	else
		wrong_input(0);
	return (0);
}
