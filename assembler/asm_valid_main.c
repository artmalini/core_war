/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_valid_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:30:41 by vmakahon          #+#    #+#             */
/*   Updated: 2018/06/08 15:30:43 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			cut_cmt_str_args(t_core *file, char *old_str)
{
	int		i;
	int		len;

	i = 0;
	if (!file || !old_str)
		return (ft_error_int(file, ERROR_FT_ARG));
	len = (int)ft_strlen(old_str);
	while (len > i && !ft_strchr("#;", old_str[i]))
		i++;
	while (len != i && len > i)
		old_str[i++] = '\0';
	if (len == i)
		return (OKAY);
	return (ERROR);
}

char		*create_str_args(t_core *file, t_cmd *c, size_t len)
{
	char	*str_args;

	if (!file || !c || !len || !(str_args = ft_memalloc(len + 5)))
	{
		ft_error(file, ERROR_FT_ARG);
		return (NULL);
	}
	if (c->args[FIRST] && c->nbr_args >= 1)
	{
		str_args = ft_strcat(str_args, c->args[FIRST]);
	}
	if (c->args[SECOND] && c->nbr_args >= 2)
	{
		str_args = ft_strcat(str_args, ", ");
		str_args = ft_strcat(str_args, c->args[SECOND]);
	}
	if (c->args[THIRD] && c->nbr_args >= 3)
	{
		str_args = ft_strcat(str_args, ", ");
		str_args = ft_strcat(str_args, c->args[THIRD]);
	}
	return (str_args);
}

void		insert_args_lst(t_core *file, t_cmd *c)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (!file || !c)
		return (ft_error(file, ERROR_FT_ARG));
	if (check_arg_of_cmd(file, c) == ERROR)
		return (ft_error(file, ERROR_TYPE_ARG));
	while (c->nbr_args > i)
		len += ft_strlen(c->args[i++]);
	c->str = create_str_args(file, c, len);
}

int			create_fresh_args(t_core *file, t_cmd *c, char **old_args)
{
	int		i;
	int		nbr;

	nbr = 0;
	if (!file || !old_args || c->nbr_args >= MAX_ARGS_NUMBER)
		return (ft_error_int(file, ERROR_FT_ARG));
	while (c->nbr_args > nbr && old_args[nbr])
	{
		i = 0;
		while (old_args[nbr][i] && ft_strchr(SPACES_CHARS, old_args[nbr][i]))
			i++;
		c->args[nbr] = ft_strdup(old_args[nbr] + i);
		i = 0;
		while (c->args[nbr][i] && !ft_strchr(SPACES_CHARS, c->args[nbr][i]))
			i++;
		c->args[nbr][i] = '\0';
		nbr++;
	}
	return (OKAY);
}

int			valid_args_main(t_core *file, t_cmd *c, char *old_args)
{
	int		i;
	char	**tmp_args;

	if (!file || !c || !old_args)
		return (ft_error_int(file, ERROR_FT_ARG));
	if (cut_cmt_str_args(file, old_args) == ERROR)
		return (ft_error_int(file, ERROR_ARG));
	if (check_comma_args(file, c, old_args))
		return (ft_error_int(file, ERROR_NBR_ARG));
	if (!(tmp_args = ft_strsplit(old_args, ',')))
		return (ft_error_int(file, ERROR_MEMORY));
	i = 0;
	while (tmp_args[i] != NULL)
		i++;
	if (i != c->nbr_args || i >= MAX_ARGS_NUMBER)
		return (ft_error_int(file, ERROR_NBR_ARG));
	if (check_args_main(file, c, tmp_args) == OKAY)
	{
		create_fresh_args(file, c, tmp_args);
		free_mas(tmp_args);
		return (OKAY);
	}
	free_mas(tmp_args);
	return (ft_error_int(file, ERROR_ARG));
}
