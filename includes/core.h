/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:06:13 by amakhiny          #+#    #+#             */
/*   Updated: 2018/05/30 16:06:17 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H
# include "../libft/lib_include/libft.h"
# include "../libft/lib_include/get_next_line.h"
# include "../libft/lib_include/ft_printf.h"
# include "../op.h"
# include <fcntl.h>

typedef struct		s_op
{
	char			*name;
	int				nbr_args;
	char			type_params[MAX_ARGS_NUMBER];
	int				opcode;
	int				cycles;
	char			*full_name;
	char			params_byte;
	char			size;
}					t_op;

extern t_op op_tab[17];

typedef struct		s_cmd
{
	char			*command;
	int				opcode;	
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_inst
{
	char			*label;
	t_cmd			*cmd;
	struct s_inst	*next;
}					t_inst;

typedef struct		s_core
{
	char			*name;
	char			*comment;
	char			*filename;
	int				rows;
	int				inst_pos;
	t_inst			*inst;
}					t_core;

void	name_and_cmt(char *line, t_core *file);
void	wrong_input(int c);
void	free_struct_tcore(t_core *file);
void	error_file(t_core *file);

#endif
