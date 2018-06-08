/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 11:46:37 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/08 11:46:42 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_hexa_fd(long code, int fd)
{
	if (code >= 256)
	{
		//ft_printf("1CODE %ld %ld\n", code / (256), code % (256));
		asm_hexa_fd(code / 256, fd);
		asm_hexa_fd(code % 256, fd);
	}
	else
	{
		//ft_printf("CODE %ld\n", code);
		ft_putchar_fd(code, fd);
	}
}
void	set_cor_magic(int fd)
{
	ft_putchar_fd(0, fd);
	asm_hexa_fd(COREWAR_EXEC_MAGIC, fd);
}

void	set_cor_name(int fd, t_core *file)
{
	char	*name;
	int		i;

	i = -1;
	name = file->name;
	while (name[++i])
		ft_putchar_fd(name[i], fd);
	while (++i < PROG_NAME_LENGTH + 1)
		ft_putchar_fd(0, fd);
	i = -1;//for null delimeter
	while (++i < 4)
		ft_putchar_fd(0, fd);
}

void	set_cor_nbr_comment(int fd, t_core *file)
{
	char	*comment;
	int		nb;
	int		i;

	i = 0;
	nb = file->count_size;
	comment = file->comment;
	while (nb)
	{		
		nb /= 256;
		i++;
	}
	while (4 - i++)//for count byte size
		ft_putchar_fd(0, fd);
	asm_hexa_fd(file->count_size, fd);
	i = -1;
	while (comment[++i])
		ft_putchar_fd(comment[i], fd);
	while (++i < COMMENT_LENGTH + 1)
		ft_putchar_fd(0, fd);
	i = -1;//for null delimeter
	while (++i < 4)
		ft_putchar_fd(0, fd);
}






void	set_bytes(int fd, char *str, t_core *file)
{
	int		i;
	int		j;
	int		nb;
	int		nbr;
	int		size;

	i = 0;
	j = 0;
	nb = 0;
	ft_printf("STR |%s|\n", str);
	size = op_tab[file->inst_pos].size;
	if (size == 0)
		j = 4;
	if (size == 1)
		j = 2;
	if (*str >= '0' && *str <= '9')
		nb = ft_atoi(str);
	else if (*str == 'r')
	{
		nb = ft_atoi(str + 1);
	}
	//else if (*str == 'r' && *str == ':')
	//{
		
	//}
	nbr = nb;
	while (nbr)
	{		
		nbr /= 256;
		j++;
	}
	printf("NB|%d| j|%d|\n", nb, j);
	while (size - i++)//for count byte size
		ft_putchar_fd(0, fd);
	asm_hexa_fd(nb, fd);
}

void	set_instruction(int fd, t_inst *inst, t_core *file)
{
	t_cmd	*comm;
	int	opcode;
	int	i;
	
	i = 0;
	while (inst)
	{
		//ft_printf("Label (Name/Positions): [%s]/[%d]\n", inst->label, inst->label_pos);
		comm = inst->cmd;
		while (comm)
		{
			i = 0;
			ft_printf("opcode %d\n", comm->opcode);
			asm_hexa_fd(comm->opcode, fd);
			check_command(comm->command, file);//	FIND current command
			//ft_printf("comm->command %d\n", file->inst_pos);
			if (op_tab[file->inst_pos].codage)
			{
				//ft_printf("str |%s|\n", comm->str);
				opcode = count_opcode(comm->str);
				ft_printf("COUNT_CODAGE %d\n", opcode);
				asm_hexa_fd(opcode, fd);
			}
			while (i < op_tab[file->inst_pos].nbr_args)
			{
				if (i == 0)
					set_bytes(fd, comm->arg1, file);
				i++;
			}
			comm = comm->next;
		}
		inst = inst->next;
	}
}

void	create_cor(t_core *file)
{
	int		fd;

	if (!(fd = open(file->filename, O_RDWR | O_CREAT, 0777)))
		error_file(file);
	set_cor_magic(fd);
	set_cor_name(fd, file);
	set_cor_nbr_comment(fd, file);
	set_instruction(fd, file->inst, file);
	if(close(fd) == -1)
		error_file(file);
}
