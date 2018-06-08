/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:30:41 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/08 15:30:43 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_arg_reg(char *arg, t_core *file)
{
	(void)file;
	int		i;

	i = 0;
	ft_printf("-------->>> T_REG: [%s]\n", (arg+i));
	return (OK);
}

int			check_arg_dir(char *arg, t_core *file)
{
	(void)file;
	int		i;

	i = 0;
	ft_printf("-------->>> T_DIR: [%s]\n", (arg+i));
	return (OK);
}

int			check_arg_ind(int arg, t_core *file)
{
	(void)file;
	int		i;

	i = 0;
	ft_printf("-------->>> T_IND: [%d]\n", arg);
	return (OK);
}

void		valid_args(char *str, t_core *file)
{
	char	**args;//NEED FREE!!!!
	int		nbr_arg;
	int		spc[3];

	nbr_arg = 0;
	args = NULL;
	ft_bzero(spc, sizeof(spc));
	if (!str || !file)
	{
		ft_printf("ERROR: Wrong args\n");
		exit(ERROR);
	}
	args = ft_strsplit(str, ',');//NEED FREE!!!!!!!!
	// ft_printf("########## -------->>> 	[%s]:[%d]\n", str, i);
	while (args[nbr_arg])
	{
		while (ft_strchr(SPACES_CHARS, args[nbr_arg][spc[nbr_arg]]))//CLEAN SPACES
			spc[nbr_arg]++;
		if (args[nbr_arg][spc[nbr_arg]] == 'r')
			check_arg_reg(args[nbr_arg]+spc[nbr_arg], file);
		else if (args[nbr_arg][spc[nbr_arg]] == '%')
			check_arg_dir(args[nbr_arg]+spc[nbr_arg], file);
		else
			check_arg_ind((short int)(ft_atoi(args[nbr_arg])), file);
		ft_printf("ARG[%d]:	[%s]\n", nbr_arg, args[nbr_arg]);
		nbr_arg++;
	}
}