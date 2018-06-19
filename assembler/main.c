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

void    display_header(void)
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

void	param_error(char *arg)
{	
	ft_putstr(arg);
	ft_putchar(' ');
}

void	err_parser(int argc, char **argv)
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

void	final(t_core *file)
{
	display_header();
	ft_putstr("Writing output program to \033[32m");
	ft_putstr(file->filename);
	ft_putstr("\033[0m\n");
}

int     main(int argc, char **argv)
{
	t_core  file;

	if (argc == 2)
	{
		ft_bzero(&file, sizeof(t_core));
		set_settings(&file, ON);                                                 //ON or OFF Settings Project
		if (!parse_filename(argv[1], &file))
			error_cor(&file, 1);
		parse_file(argv[1], &file);


		ft_printf("\n\n");
		label_debug(&file);//LABEL DEBUG
		ft_printf("\n");
		cmd_debug(file.inst);///COMMAND debug       
		ft_printf("\n");
		ft_printf("OK Rows: [%d]\n", file.rows);

		recalc_cmd_links(&file);    
		create_cor(&file, argv[1]);
		final(&file);
		free_struct_tcore(&file);
	}
	else
		err_parser(argc, argv);
	return (0);
}