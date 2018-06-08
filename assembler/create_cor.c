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

void	create_cor(t_core *file)
{
	int		fd;

	if (!(fd = open(file->filename, O_RDWR | O_CREAT, 0777)))
		error_file(file);
	set_cor_magic(fd);
	set_cor_name(fd, file);
	set_cor_nbr_comment(fd, file);
	if(!close(fd))
		error_file(file);
}
