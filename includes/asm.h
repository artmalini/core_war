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

/*
**					[Includes Library]
*/

# include "op.h"
# include "color.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
//# include <opencl-c.h>
//# include <limits.h>

/*
**					[Macros for ERROR MANAGER]
*/

# define ON			1
# define OFF		0
# define NAME		1
# define COMMENT	2

# define FIRST		0
# define SECOND		1
# define THIRD		2

# define OKAY			0
# define ERROR			-1

# define ERROR_OPEN		100
# define ERROR_READ		101
# define ERROR_CLOSE	102
# define ERROR_INPUT	103

# define ERROR_NAME		104
# define ERROR_L_NAME	105
# define ERROR_S_NAME	106

# define ERROR_CMT		107
# define ERROR_L_CMT	108
# define ERROR_S_CMT	109

# define ERROR_LABEL	110
# define ERROR_ID_LABEL	111
# define ERROR_SYNTAX	112
# define ERROR_MEMORY	113
# define ERROR_CMD		114

# define ERROR_A_NAME	115
# define ERROR_A_CMT	116

# define ERROR_LINE		117
# define ERROR_ARG		118
# define ERROR_FT_ARG	119

# define ERROR_T_DIR	120
# define ERROR_T_IND	121
# define ERROR_NBR_ARG	122
# define ERROR_ID_ARG	123
# define ERROR_TYPE_ARG	124

# define ERROR_1		125
# define ERROR_2		126
# define ERROR_3		127
# define ERROR_4		128

/*
**					[Macros for easy reading code]
*/

# define CMD			(c->opcode -1)
# define OP(CMD)		(op_tab[CMD])
# define SIZE(CMD)		(op_tab[CMD].size)
# define NBR_ARGS(CMD)	(op_tab[CMD].nbr_args)
# define TYPE_ARG(nbr)	(op_tab[CMD].type_params[nbr])

/*
**					[Typedef and Structs Part]
*/

typedef char 		t_arg_type;

typedef struct		s_error
{
	int				id;
	char 			*arg;
	char 			*cmd;
	int 			usage;
	int				*rows;
	char 			*label;
	char 			*current_arg;

}					t_error;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			how[COMMENT_LENGTH + 1];
} 					t_header;

typedef struct		s_cmd
{
	char			*command;
	char			*str;
	char 			*args[MAX_ARGS_NUMBER];//Need free new **array args.
	int				opcode;
	int				cmd_size;
	int				byte_nbr;
	int				cmd_str_size;
	int 			nbr_args;
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
	t_inst			*inst;
	t_error			*error;
	char			*name;
	char			*comment;
	char			*filename;
	int				flag;
	int				syntax;
	int				cmt_nbr;
	int				inst_pos;
	int				name_nbr;
	int				point_nbr;
	int				name_length;
	int				cmt_length;
	int				count_size;
}					t_core;

/*
**					[PARSE PART]
*/

int			line_has_val(char *line);
void		recalc_cmd_links(t_core *file);
void		parse_header(t_core *file, int fd);
void		read_line(t_core *file, char *line);
void		name_cmt_valid(t_core *file, char *str);
void		rebuild_name_cmt(t_core *file, int len);
int			check_command(t_core *file, char *lowstr);
int			len_check(t_core *file, int type, int len);
void		name_cmt(t_core *file, char *str, int type);
void		find_l(t_cmd *tmp, char *str, int label_pos);
void		parse_file(t_core *file, char *arg, char *line);
void		read_init_line(t_core *file, char *line, int nb);
int			parse_filename(t_core *file, char *arg, int len);
t_inst		*add_label(t_core *file, t_inst	*lst, char *str);
t_cmd		*add_cmd(t_core *file, char *cmd, char *str_args);
int			parse_header_name(t_core *file, char *str, int i);
int			count_cmd_size(t_core *file, t_cmd *c, int l_size);
void		push_laybel(t_core *file, t_inst **lst, char *str);
void		line_handler(t_core *file, char *line, char *lowstr);
void		push_cmd(t_core *file, t_cmd **lst, char *cmd, char *args);
char		*line_finalize(t_core *file, char **str, char *lowstr, int *i);

/*
**					[ASM FILE .cor]
*/

int			count_opcode(char *str);
int			get_binary_code(char c);
void		asm_hexa_fd(long code, int fd);
void		create_cor(t_core *file, int fd);
void		set_cor_name(t_core *file, int fd);
int			find_nbr_bytes(char *str, int size);
void		set_cor_nbr_comment(t_core *file, int fd);
int			result_opcode(char c, int code, int get_bin);
int			negative_nbr(int nb, int size, t_core *file);
void		set_instruction(t_core *file, t_cmd *c, int fd);
void		set_bytes(int fd, char *str, t_core *file, t_cmd *c);
void		set_bytes_zero_alignment(int fd, int size, int nb, int nbr);
int			find_pos_cmd(t_core *file, t_inst *inst, char *str, int cmd_size);

/*
**					[ERROR MANAGER]
*/

char 		*ft_str_asma(int id);
char 		*ft_str_asmb(int id);
void		ft_init(t_core *file);
void 		ft_error(t_core *file, int id);
int 		ft_error_int(t_core *file, int id);

/*
**					[VALIDATION ARGUMENTS]
*/

void		insert_args_lst(t_core *file, t_cmd	*c);
int			check_arg_of_cmd(t_core *file, t_cmd *c);
int			cut_cmt_str_args(t_core *file, char *old_str);
int			check_arg_ind(t_core *file, t_cmd *c, char *arg);
int			check_arg_reg(t_core *file, t_cmd *c, char *str_arg);
int			check_arg_dir(t_core *file, t_cmd *c, char *str_arg);
int			check_args_main(t_core *file, t_cmd *c, char **args);
char		*create_str_args(t_core *file, t_cmd *c, size_t len);
int			check_arg_label(t_core *file, t_cmd *c, char *str_arg);
int			valid_args_main(t_core *file, t_cmd *c, char *old_args);
int 		create_fresh_args(t_core *file, t_cmd *c, char **old_args);

/*
**					[DEBUG and PRINT]
*/

void		final(t_core *file);
void		display_header(void);
void		param_error(char *arg);
void		err_parser(int argc, char **argv);

/*
**					[FREE MEMORY]
*/

void		free_mas(char **mas);
void		cmd_free(t_cmd *c);
void		cmd_lst_free(t_cmd *c);
void		inst_free(t_inst *first);
void		inst_data_free(t_inst *inst);
void		free_struct_tcore(t_core *file);

#endif
