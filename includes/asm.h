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

//  Macros for [Includes Library]

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <limits.h>

//  Macros for [ERROR MANAGER]

# define OK		    1
# define ERROR	    -1
# define ERROR_ARG  1

//  Macros for [Debugs] and [Settings]

# define ON		    1
# define OFF		0

# define FIRST	    0
# define SECOND	    1
# define THIRD	    2

# define DEBUG_ON	0
# define DEBUG_LB	1
# define DEBUG_CMD	2
# define DEBUG_ARG	3

//  Macros for [ARGUMENTS] and [Labels]

# define T_REG	    1
# define T_DIR  	2
# define T_IND	    4
# define T_LAB	    8

# define IND_SIZE   2
# define REG_SIZE   4
# define DIR_SIZE   REG_SIZE

# define REG_CODE   1
# define DIR_CODE   2
# define IND_CODE   3

# define INT32      3

//  Macros for [Virtual Machine]

# define MAX_ARGS_NUMBER    4
# define MAX_PLAYERS        4
# define MEM_SIZE           (4 * 1024)
# define IDX_MOD            (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE     (MEM_SIZE / 6)

# define REG_NUMBER         16

//  Macros for [Validations]

# define COMMENT_CHAR       '#'
# define COMMENT_CHAR2      ';'
# define LABEL_CHAR         ':'
# define DIRECT_CHAR        '%'
# define SEPARATOR_CHAR     ','

# define PROG_NAME_LENGTH   (128)
# define COMMENT_LENGTH     (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

# define NAME_CMD_STRING    ".name"
# define COMMENT_CMD_STRING ".comment"

# define SPACES_CHARS       "\t \v"
# define LABEL_CHARS        "abcdefghijklmnopqrstuvwxyz_0123456789"

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
	int				byte_nbr;
	int				cmd_str_size;
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
	int				flag;
	int				point_nbr;
	int				syntax;
	int				name_nbr;
	int				cmt_nbr;
	int				name_length;
	int				cmt_length;

	char			*name;
	char			*comment;
	char			*filename;
	int				rows;
	int				inst_pos;
	t_inst			*inst;
	int				count_size;
    int             st[10];//for settings
}					t_core;

extern t_op	op_tab[17];

t_inst		*add_label(char *str, t_core *file);
int			line_has_val(char *line);
void		read_line(char *line, char *arg, t_core *file);
void		parse_file(char *arg, t_core *file);
void		push_laybel(char *str, t_inst **lst, t_core *file);
void		name_and_cmt(char *line, t_core *file);
//int			line_label(char *line, t_core *file);
void		line_handler(char *line, char *arg, t_core *file);
int			parse_filename(char	*arg, t_core *file);
int			check_command(char	*lowstr, t_core *file);
t_cmd		*add_cmd(char *cmd, char *args, t_core *file);
void		push_cmd(char *cmd, char *args, t_core *file, t_cmd **lst);
void		create_cor(t_core *file, char *arg);
int			count_opcode(char *str);


//			[ERROR MANAGER]

void		wrong_input(int c, char *arg, t_core *file);
void		error_file(t_core *file, char *arg, int nbr_char);
void		error_cor(t_core *file, int nbr_char);


//			[VALIDATION ARGUMENTS]

int		    ft_isspace(char c);
int			check_arg_reg(t_core *file, char *str_arg, int nbr_arg);
int			check_arg_dir(t_core *file, char *str_arg, int nbr_arg);
int			check_arg_ind(t_core *file, char *str_arg, int nbr_arg);
int 		check_args_main(t_core *file, char **args, int nbr_args);
int			check_arg_label(t_core *file, char *str_arg, int nbr_arg);
char		**create_fresh_args(t_core *file, char **args, int nbr_args);
char		**valid_args_main(t_core *file, char *str_args, int nbr_args);
char        *create_str_args(t_core *file, t_cmd *lst, size_t len, int nbr);
void        insert_args_lst(t_core *file, t_cmd	*lst, char **args, int nbr);


//			[DEBUG and PRINT]

void		cmd_debug(t_inst *inst);
void		label_debug(t_core *file);
void        set_settings(t_core	*file, int flag);
void		print_new_args(t_core *file, t_cmd	*lst, char **args, int nbr_args);

//			[FREE MEMORY]

void		free_mas(char **mas);
void		free_struct_tcore(t_core *file);

#endif