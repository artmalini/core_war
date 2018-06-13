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

#include "asm.h"

int		line_has_val(char *line)
{
	while (*line)
	{
		if (*line != '\t' && *line != ' ')
			return (1);
		line++;
	}
	return (0);	
}

int		check_command(char	*lowstr, t_core *file)
{
	int		i;

	i = -1;
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



/*void	line_handler(char *line, t_core *file)
{
	int		i;
	char	*str;
	char	*lowstr;

	i = 0;
	str = line;
	lowstr = NULL;
	//while (*str && (*str == ' ' || *str == '\t'))
	//	str++;
	while (str[i] && str[i] != ':' && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] == ':')//label exist, if i == 0 should be error!
	{
		if (i == 0)
		{
			ft_printf("Label must be at least one character ");
			error_file(file, 0);
		}
		lowstr = ft_strsub(str, 0, i);
		push_laybel(lowstr, &file->inst, file);
		ft_printf("\n---> Finded LABEL: [%s]\n", lowstr);
		ft_strdel(&lowstr);
		while (*str && ft_strchr(LABEL_CHARS, *str) && *str != ':')
			str++;
		str++;//!!!!!for :
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		i = 0;
		if (*str)
		{
			ft_printf("** Analyze String: [%s]\n", str);
			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			{
				if (!ft_strchr(LABEL_CHARS, str[i]))
				{
					ft_printf("!! Line_handler:	ERROR\n");
					error_file(file, 0);
				}
				i++;
			}
			lowstr = ft_strsub(str, 0, i);
		}
		else
		{
			ft_strdel(&lowstr);
			return ;
		}
	}	
	else
		lowstr = ft_strsub(str, 0, i);
	if (check_command(lowstr, file))
	{
		ft_printf("** Check_commands: [%s]%s|%d\n", lowstr, str + (ft_strlen(lowstr) + 1), i);
		if (!file->inst)//!!!!!!!!!  IF LABEL DOES NOT EXIST
			push_laybel(NULL, &file->inst, file);
		push_cmd(lowstr, str + (ft_strlen(lowstr) + 1), file, &file->inst->cmd);
	}
	else
		error_file(file, 0);//wrong command
	ft_strdel(&lowstr);
}*/

int		label_check(int i, char *str, t_core *file)
{
	int		len;

	len = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
		{
			ft_printf("!! Line_handler:	ERROR\n");
			error_file(file, 0);
		}
		len = i++;
	}
	return (len);
}

int		label_counter(int j, char *str)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str)
	{
		ft_printf("** Analyze String: [%s]\n", str);
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			len = i++;
	}
	else
		len = j;
	return (len);
}

char	*label_handler(int i, char *str, t_core *file)
{
	char	*lowstr;

	lowstr = NULL;
	i = 0;
	if (*str)
	{
		ft_printf("** Analyze String: [%s]\n", str);
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
			{
				ft_printf("!! Line_handler:	ERROR\n");
				error_file(file, 0);
			}
			i++;
		}
		lowstr = ft_strsub(str, 0, i);
	}
	else
	{
		//ft_strdel(&lowstr);
		return (NULL);
	}
	return (lowstr);
}





void	line_handler(char *line, t_core *file)
{
	int		i;
	char	*str;
	char	*lowstr;

	i = 0;
	str = line;
	lowstr = NULL;
	//while (*str && (*str == ' ' || *str == '\t'))
	//	str++;
	while (str[i] && str[i] != ':' && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] == ':')//label exist, if i == 0 should be error!
	{
		if (i == 0)
		{
			ft_printf("Label must be at least one character ");
			error_file(file, 0);
		}
		lowstr = ft_strsub(str, 0, i);
		push_laybel(lowstr, &file->inst, file);
		ft_printf("\n---> Finded LABEL: [%s]\n", lowstr);
		ft_strdel(&lowstr);
		while (*str && ft_strchr(LABEL_CHARS, *str) && *str != ':')
			str++;
		str++;//!!!!!for :
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		i = 0;
		if (*str)
		{
			ft_printf("** Analyze String: [%s]\n", str);
			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			{
				if (!ft_strchr(LABEL_CHARS, str[i]))
				{
					ft_printf("!! Line_handler:	ERROR\n");
					error_file(file, 0);
				}
				i++;
			}
			//i = label_check(i, str, file);
			lowstr = ft_strsub(str, 0, i);
		}
		else
		{
			ft_strdel(&lowstr);
			return ;
		}
	}	
	else
		lowstr = ft_strsub(str, 0, i);
	if (check_command(lowstr, file))
	{
		ft_printf("** Check_commands: [%s]%s|%d\n", lowstr, str + (ft_strlen(lowstr) + 1), i);
		if (!file->inst)//!!!!!!!!!  IF LABEL DOES NOT EXIST
			push_laybel(NULL, &file->inst, file);
		push_cmd(lowstr, str + (ft_strlen(lowstr) + 1), file, &file->inst->cmd);
	}
	else
		error_file(file, 0);//wrong command
	ft_strdel(&lowstr);
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
	while (*str)
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



void			find_l(char *str, t_cmd *file, int label_pos)
{
	t_cmd	*tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->arg1)
		{
			if (!ft_strcmp(str, tmp->arg1 + 2))// %:
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->arg1 + 1))// :
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		if (tmp->arg2)
		{
			if (!ft_strcmp(str, tmp->arg2 + 2))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->arg2 + 1))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		if (tmp->arg3)
		{
			if (!ft_strcmp(str, tmp->arg3 + 2))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
			if (!ft_strcmp(str, tmp->arg3 + 1))
					tmp->cmd_str_size = label_pos - tmp->cmd_str_size;
		}
		tmp = tmp->next;	
	}
}


void			recalc_cmd_links(t_core *file)
{
	t_inst	*tmp;

	tmp = file->inst;
	if (tmp)
	{
		while (tmp)
		{
			//tmp->label_pos = find_l(tmp->label, file->inst->cmd, tmp->label_pos);
			if (tmp->label)
				find_l(tmp->label, file->inst->cmd, tmp->label_pos);
			ft_printf("														NEXT\n");
			tmp = tmp->next;
		}
	}
}


int		main(int argc, char **argv)
{
	t_core	file;

	if (argc == 2)
	{
		ft_bzero(&file, sizeof(t_core));
        set_settings(&file, ON);                                                 //ON or OFF Settings Project
		if (!parse_filename(argv[1], &file))
			wrong_input(1);
		parse_file(argv[1], &file);


		ft_printf("\n\n");
		label_debug(&file);//LABEL DEBUG
		ft_printf("\n");
		cmd_debug(file.inst);///COMMAND debug		
		ft_printf("\n");
		ft_printf("OK Rows: [%d]\n", file.rows);

		recalc_cmd_links(&file);	
		create_cor(&file);

		free_struct_tcore(&file);

		
		//ft_printf("$$$|%d|\n", ((112 & 11000000) >> 6));
		//ft_printf("$$$|%d|\n", ((112 >> 4) & 0x3));
		//system("leaks asm");
	}
	else
		wrong_input(0);
	return (0);
}