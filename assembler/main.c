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

int		main(int argc, char **argv)
{
	t_core	file;

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

		free_struct_tcore(&file);
	}
	else
		error_cor(&file, 1);
	return (0);
}