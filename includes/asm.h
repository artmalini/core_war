/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:06:13 by amakhiny          #+#    #+#             */
/*   Updated: 2018/05/30 16:06:17 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define COMMENT_CHAR '#'
# define COMMENT_CHAR2 ';'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

# define HEADER_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789! '()-+*&<>=/ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

typedef char 		t_arg_type;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name [PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			how [COMMENT_LENGTH + 1];
} 					t_header;

typedef struct		s_op
{
	char			*name;
	int				nbr_args;
	char			type_params[MAX_ARGS_NUMBER];
	int				opcode;
	int				cycles;
	char			*full_name;
	int				codage;
	int				size;
}					t_op;

typedef struct		s_cmd
{
	char			*command;
	char			*str;
	char			*arg1;
	char			*arg2;
	char			*arg3;
	int				opcode;
	int				cmd_size;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_inst
{
	char			*label;
	t_cmd			*cmd;
	int				label_pos;
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
	int				size;
	int				count_size;
}					t_core;

extern t_op op_tab[17];

char	*inter_main(void);
void	wrong_input(int c);
t_inst	*add_label(char *str, t_core *file);
int		line_has_val(char *line);
void	error_file(t_core *file);
void	free_struct_tcore(t_core *file);
void	read_line(char *line, t_core *file);
void	parse_file(char *arg, t_core *file);
void	push_laybel(char *str, t_inst **lst, t_core *file);
void	name_and_cmt(char *line, t_core *file);
void	line_handler(char *line, t_core *file);
int		parse_filename(char	*arg, t_core *file);
int		check_command(char	*lowstr, t_core *file);
t_cmd	*add_cmd(char *cmd, char *args, t_core *file);
void	push_cmd(char *cmd, char *args, t_core *file, t_cmd **lst);
void	create_cor(t_core *file);

void	cmd_debug(t_inst *inst);
void	label_debug(t_core *file);

#endif