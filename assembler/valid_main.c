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

void        insert_args_lst(t_core *file, t_cmd	*lst, char **args, int nbr)
{
    if (!file || !args || !nbr)
    {
        error_cor(file, ERROR_ARG);
        return ;
    }
    lst->arg1 = nbr > 0 ? ft_strdup(args[FIRST]) : NULL;
    lst->arg2 = nbr > 1 ? ft_strdup(args[SECOND]) : NULL;
    lst->arg3 = nbr > 2 ? ft_strdup(args[THIRD]) : NULL;
}

char		**create_fresh_args(t_core *file, char **args, int nbr_args)
{
    int     i;
    int     nbr;
    char    **new_args;

    nbr = 0;
    if (nbr_args >= MAX_ARGS_NUMBER)
    {
        error_cor(file, ERROR_ARG);
        return (NULL);
    }
    new_args = ft_memalloc(sizeof(new_args) * (nbr_args + 1));                  //Need Free Memory
    while (nbr_args > nbr && args[nbr])
    {
        i = 0;
        while (args[nbr][i] && ft_isspace(args[nbr][i]))
            i++;
        new_args[nbr] = ft_strdup(args[nbr] + i);                               //Need Free Memory
        nbr++;
    }
    return (new_args);
}


char		**valid_args_main(t_core *file, char *str_args, int nbr_args)
{
    char	**args;
    char    **new_args;

	args = ft_strsplit(str_args, ',');									        //Need free memory
    if (!args || !file || !nbr_args)                                            //Search Errors
        error_cor(file, ERROR_ARG);
	if (check_args_main(file, args, nbr_args) == OK)                            //Main Check Arguments
    {
        new_args = create_fresh_args(file, args, nbr_args);                     //Create new args without spaces
        free_mas(args);                                                         //Free memory
        return (new_args);
    }
	else
	{
		error_cor(file, ERROR_ARG);
		free_mas(args);															//Free memory
		return (NULL);
	}
}
