/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_create_cor_instr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:03:38 by amakhiny          #+#    #+#             */
/*   Updated: 2018/06/18 14:03:42 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			find_nbr_bytes(const char *str, int size)
{
	int		nbr;

	nbr = (size == 0) ? 4 : 2;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
		nbr = 2;
	else if (str[0] == 'r')
		nbr = 1;
	else if (str[0] == ':')
		nbr = 2;
	return (nbr);
}

long		negative_nbr(t_core *file, int nb, int size)
{
	long	nbr;

	nbr = 0;
	if (size == 2)
	{
		if (nb < -65536)
			return (ft_error_int(file, ERROR_SYNTAX));
		nbr = 65536 + nb;
	}
	if (size == 4)
	{
		if (nb >= 0)
			nbr = 2147483648 + nb;
		else
			nbr = 4294967296 + nb;
	}
	return (nbr);
}

void		set_bytes_zero_alignment(int fd, int size, int nb, int nbr)
{
	int		j;

	j = 0;
	while (nbr)
	{
		nbr /= 256;
		j++;
	}
	if (nb == 0)
		size -= 1;
	if (nb >= 0)
	{
		while (size - j++)
			ft_putchar_fd(0, fd);
	}
}

void		set_bytes(int fd, char *str, t_core *file, t_cmd *c)
{
	long	nb;
	int		nbr;
	int		size;

	nb = 0;
	size = find_nbr_bytes(str, op_tab[file->inst_pos].size);
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
		nb = ft_atoi(str);
	else if (str[0] == 'r')
		nb = ft_atoi(str + 1);
	else if (str[0] == '%' && str[1] == ':')
		nb = find_pos_cmd(file, file->inst, str + 2, c->cmd_str_size);
	else if (str[0] == ':')
		nb = find_pos_cmd(file, file->inst, str + 1, c->cmd_str_size);
	else if (str[0] == '%' && str[1] != ':')
		nb = ft_atoi(str + 1);
	if (nb < 0)
		nb = negative_nbr(file, nb, size);
	nbr = (int)nb;
	set_bytes_zero_alignment(fd, size, nb, nbr);
	asm_hexa_fd(nb, fd);
}

void		set_instruction(t_core *file, t_cmd *c, int fd)
{
	t_cmd	*cmd;
	int		i;

	cmd = c;
	while (cmd)
	{
		asm_hexa_fd(cmd->opcode, fd);
		check_command(file, cmd->command);
		if (op_tab[file->inst_pos].codage)
			asm_hexa_fd(count_opcode(cmd->str), fd);
		i = -1;
		while (++i < op_tab[file->inst_pos].nbr_args)
		{
			if (i == 0)
				set_bytes(fd, cmd->args[FIRST], file, cmd);
			if (i == 1 && op_tab[file->inst_pos].nbr_args > 1)
				set_bytes(fd, cmd->args[SECOND], file, cmd);
			if (i == 2 && op_tab[file->inst_pos].nbr_args > 2)
				set_bytes(fd, cmd->args[THIRD], file, cmd);
		}
		cmd = cmd->next;
	}
}
