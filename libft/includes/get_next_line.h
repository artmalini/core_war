/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 15:04:50 by amakhiny          #+#    #+#             */
/*   Updated: 2017/12/14 18:00:34 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>

# define BUFF_SIZE 100

typedef struct		s_mem
{
	int				fd;
	char			*content;
	struct s_mem	*next;
}					t_mem;

int					get_next_line(const int fd, char **line);

#endif
