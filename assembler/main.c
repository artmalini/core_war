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
		if (*line != '\t' || *line != ' ')
			return (1);
		line++;
	}
	return (0);	
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

		ft_printf("Line[65]: line_handler	(|%s|)\n", lowstr);
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
		ft_printf("\nLine[79]: STR	|%s|\n", str);
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
			{
				ft_printf("Line[84]: line_handler	ERROR\n");
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
		ft_printf("Line[97]: line_handler check_command	|%s|	|%s|\n", lowstr, str + (ft_strlen(lowstr) + 1));
		if (!file->inst)//!!!!!!!!!  IF LABEL DOES NOT EXIST
			push_laybel(NULL, &file->inst);
		push_cmd(lowstr, str + (ft_strlen(lowstr) + 1), file, &file->inst->cmd);
	}
	else
	{//wrong command
		ft_printf("Line[104]: line_handler	ERROR\n");
		error_file(file);
	}


	ft_strdel(&lowstr);
	//ft_printf("@@@@ |%s| %d\n", str + i, i);
	//str += i;
	//ft_printf("line_handler|%s| 		str|%s|\n", line, str);	
}

int		main(int argc, char **argv)
{
	t_core	file;

	if (argc == 2)
	{
		ft_bzero(&file, sizeof(t_core));
		if (!parse_filename(argv[1], &file))
			wrong_input(1);
		parse_file(argv[1], &file);

		inter_main();//NEW FUNCTIONS (VOID);

		ft_printf("\n\n");
		label_debug(&file);//LABEL DEBUG
		ft_printf("\n");
		cmd_debug(file.inst);///COMMAND debug		
		ft_printf("\n");
		ft_printf("ok rows: [%d]\n", file.rows);

		free_struct_tcore(&file);
		//system("leaks asm");
	}
	else
		wrong_input(0);
	return (0);
}