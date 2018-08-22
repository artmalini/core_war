/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:13:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/04 16:13:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_init(t_core *file, char *argument)
{
	t_error	*new;

	if (!(new = ft_memalloc(sizeof(t_error))))
		ft_error(file, ERROR_MEMORY);
	ft_bzero(file, sizeof(t_core));
	file->error = new;
	file->error->asm_arg = ft_strdup(argument);
	file->error->current_rows = 1;
}

void		free_mas(char **mas)
{
	int		i;

	i = -1;
	if (!mas)
		return ;
	while (mas[++i] != NULL)
		free(mas[i]);
	free(mas);
}
