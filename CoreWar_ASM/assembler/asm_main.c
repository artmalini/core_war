/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:55:49 by amakhiny          #+#    #+#             */
/*   Updated: 2018/05/30 13:55:58 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	t_core	file;

	if (argc == 2)
	{
		ft_init(&file, argv[1]);
		if (parse_filename(&file, argv[1], (int)ft_strlen(argv[1])))
			return (ft_error_int(&file, ERROR_SYNTAX));
		parse_file(&file, argv[1], NULL);
		recalc_cmd_links(&file);    
		create_cor(&file, 0);
		final(&file);
		free_struct_tcore(&file);
	}
	else
		err_parser(argc, argv);
	return (EXIT_SUCCESS);
}
