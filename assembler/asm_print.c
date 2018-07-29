/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:51:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/04 15:51:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		param_error(char *arg)
{
	ft_putstr(arg);
	ft_putchar(' ');
}

void		display_header(void)
{
	ft_putstr("\033[31m");
	ft_putstr("     ___           ___           ___         \n");
	ft_putstr("    /\\  \\         /\\  \\         / \\__\\        \n");
	ft_putstr("   /::\\  \\       /::\\  \\       /::|  |       \n");
	ft_putstr("  /:/\\:\\  \\     /:/\\ \\  \\     /:|:|  |       \n");
	ft_putstr(" /::\\~\\:\\  \\   _\\:\\~\\ \\  \\   /:/|:|__|__     \n");
	ft_putstr("/:/\\:\\ \\:\\__\\ /\\ \\:\\ \\ \\__\\ /:/ |::::\\__\\ \n");
	ft_putstr("\\/__\\:\\/:/  / \\:\\ \\:\\ \\/__/ \\/__/~~/:/  /    \n");
	ft_putstr("     \\::/  /   \\:\\ \\:\\__\\         /:/  /     \n");
	ft_putstr("     /:/  /     \\:\\/:/  /        /:/  /     \n");
	ft_putstr("    /:/  /       \\::/  /        /:/  /      \n");
	ft_putstr("    \\/__/         \\/__/         \\/__/       \n\n");
	ft_putstr("\033[0m");
}

void		err_parser(int argc, char **argv)
{
	int		i;

	i = 1;
	display_header();
	ft_putstr("ERROR: Arguments ");
	while (--argc)
		param_error(argv[i++]);
	ft_putstr("is invalid!\n");
	ft_putstr("\033[33m ");
	ft_putstr(argv[0]);
	ft_putstr(" file_name.s\033[0m   To run compiler\n");
	exit(1);
}

void		final(t_core *file)
{
	display_header();
	ft_putstr("Writing output program to \033[32m");
	ft_putstr(file->filename);
	ft_putstr("\033[0m\n");
}
