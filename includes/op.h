/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:00:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/03 19:00:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
**					[Macros for Arguments and Labels]
*/

# define T_REG			1
# define T_DIR			2
# define T_IND			4
# define T_LAB			8

# define IND_SIZE		2
# define REG_SIZE		4
# define DIR_SIZE		REG_SIZE
# define REG_NUMBER		16

# define REG_CODE		1
# define DIR_CODE		2
# define IND_CODE		3

/*
**					[Macros for Validations]
*/

# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define REGISTER_CHAR		'r'
# define COMMENT_CHAR		'#'
# define COMMENT_CHAR2		';'
# define SEPARATOR_CHAR		','

# define PROG_NAME_LENGTH   (128)
# define COMMENT_LENGTH     (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

# define NAME_CMD_STRING    ".name"
# define COMMENT_CMD_STRING ".comment"

# define SPACES_CHARS       " \t\n\v\f\r"
# define LABEL_CHARS        "abcdefghijklmnopqrstuvwxyz_0123456789"
# define IN_DIRECT_CHARS	"-0123456789"

/*
**					[Macros for Virtual Machine]
*/

# define MAX_ARGS_NUMBER    4
# define MAX_PLAYERS        4
# define MEM_SIZE           (4 * 1024)
# define IDX_MOD            (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE     (MEM_SIZE / 6)

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

extern t_op			g_op_tab[17];

#endif
