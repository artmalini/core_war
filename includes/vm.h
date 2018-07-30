/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:29:13 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/06 12:29:14 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
//# include <ncurses.h>
# include "curses.h"
/*
**					[Macros for ERROR MANAGER]
*/

# define OKAY			0
# define ERROR			1
# define ERROR_OPEN		2
# define ERROR_READ		3
# define ERROR_CLOSE	4
# define ERROR_MAGIC	5
# define ERROR_NAME		6
# define ERROR_SIZE		7
# define ERROR_PLAYER	8
# define ERROR_DUP		9
# define ERROR_COMMENT	10
# define ERROR_FILE		11
# define ERROR_SFILE	12
# define ERROR_1		13
# define ERROR_2		14
# define ERROR_3		15
# define ERROR_4		16


#define IND_SIZE 2
#define REG_SIZE 4
#define DIR_SIZE REG_SIZE


#define REG_CODE 1
#define DIR_CODE 2
#define IND_CODE 3


#define MAX_ARGS_NUMBER 4
#define MAX_PLAYERS 4
#define MEM_SIZE (4 * 1024)//4096
#define IDX_MOD (MEM_SIZE / 8)//512
#define CHAMP_MAX_SIZE (MEM_SIZE / 6)

#define COMMENT_CHAR '#'
#define COMMENT_CHAR2 ';'
#define LABEL_CHAR ':'
#define DIRECT_CHAR '%'
#define SEPARATOR_CHAR ','

#define HEADER_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789! '()-+*&<>=/ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING ".name"
#define COMMENT_CMD_STRING ".comment"

#define REG_NUMBER 16

#define CYCLE_TO_DIE 1536
#define CYCLE_DELTA 50
#define NBR_LIVE 21
#define MAX_CHECKS 10

typedef char t_arg_type;

#define T_REG 1
#define T_DIR 2
#define T_IND 4
#define T_LAB 8


#define PROG_NAME_LENGTH (128)
#define COMMENT_LENGTH (2048)
#define COREWAR_EXEC_MAGIC 0xea83f3

# define BUF_SIZE (5)

typedef struct		s_error
{
	int				id;
	char			*name;

}					t_error;

// typedef struct		s_header
// {
// 	unsigned int	magic;
// 	char			prog_name [PROG_NAME_LENGTH + 1];
// 	unsigned int	prog_size;
// 	char			how [COMMENT_LENGTH + 1];
// }					t_header;



// typedef struct		s_player
// {
// 	// char			magic[8];
// 	char			*magic;
// 	// char			bot_name[PROG_NAME_LENGTH];
// 	char			*bot_name;
// 	int				size_exec;
// 	// char			comment[COMMENT_LENGTH];
// 	char			*comment;
// 	// char			ex_code[size_exec];
// 	char			*ex_code;
// 	unsigned char		memory[MEM_SIZE];
// 	unsigned int		nb_player;
// 	unsigned long		cycle;
// 	unsigned long		nbr_live;
// 	unsigned long		old_nbr_live;
// 	unsigned long		nb_process;
// 	int					mem_mov;
	
// } 					t_player;


//  для команд
// typedef struct		s_proc
// {
// 	int				carry;
// 	int				pc;
// 	int				reg[REG_NUMBER];
// 	int				instruction;
// 	int				cycle_to_wait;
// 	int				live_period;
// 	int				id;
// 	int				parametres_types[5];
// 	int				save_pc;
// 	int				alive;
// 	struct s_proc	*next;
// }					t_proc;
typedef struct 		s_cmd
{
	int				reg[REG_NUMBER];
	int				pl;
	int				idx;
	int				rgb;
	int				off;
	int				carry;
	int				wait;
	int				playing;
	int				flag;
	int				life;	
	int				nbr_process;
	int				on;
	int				previdx;
	int				str_cycle;
	int				lnew;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

// tvertohr and
typedef struct		s_proc
{
	int				carry;
	int				pc;
	int				reg[REG_NUMBER];
	int				instruction;
	int				cycle_to_wait;
	int				live_period;
	int				id;
	int				parametres_types[3];
	int				save_pc;
	int				alive;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_arena
{
	char			acb;

	char			o_acb;
	int				hit;
	int				pl;

	int				rgb;//main color for chars on arena
	int				asc_rgb;
	int				flag;
	int				bold;	
}					t_arena;

typedef struct		s_champ
{
	int				id;
	char			*name;
	char			comment[COMMENT_LENGTH];
	int				magic_number;
	int				weight;
	int				rgb;

	int				idx;
	//int			life;
	int				nbr_process;
	int				alive;
	int				old_check;
	int				prev_live;
	int				lives_in_period;	
	char			*prog;
}					t_champ;

typedef struct		s_vm
{
	int				fd;
	int				dump_cycle;
	t_champ			tab_champ[MAX_PLAYERS];
	t_cmd			*cmd;
	int				nbr_next;
	t_arena			arena[MEM_SIZE];
	int				last_check;
	int				cycle;
	int				cycle_to_die;
	int				cycle_before_checking;
	int				total_lives_period;
	int				lifes;
	int				total_process;
	int				total_cycle;
	int				win;
	int				aff;
	int				debug;
	int				visual;
}					t_vm;

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

extern t_op			op_tab[17];

int					vm_usage(void);
int					vm_param_n(t_vm *vm, char **av, int *i, int ac);
int					vm_isnumber(char *str);
int					vm_get_param(char **av, t_vm *vm, int ac);
void				vm_init(t_vm *vm);
void				vm_create_arena(t_vm *vm);
void				vm_load_lists(t_cmd **cmd, t_vm *vm);
void				vm_glow_cur(t_vm *vm, t_cmd *cmd);
void				vm_dump_arena(t_vm *vm);
void				vm_create_arena(t_vm *vm);
void				vm_load_arena(t_vm *vm);
void				vm_cmd_triger(t_vm *vm, t_cmd *cmd, int hex);
void				vm_cycler_to_die(t_vm *vm, int *i);
int					vm_its_cmd(t_vm *vm, t_cmd *cmd);
void				vm_load_champs(t_vm *vm);
void				vm_read_champ(t_vm *vm, int number_player);
void				vm_dump_arena(t_vm *vm);
void				vm_exit(t_vm *vm);


void				ft_print_error(t_error *e);
char				*vm_str_error(int error);
void				free_vm(t_vm *vm);
void				vm_exit(t_vm *vm);

int					mdx(int nbr);
int					vm_pos_curs(t_vm *vm, t_cmd *cmd);
void				vm_next_step(t_vm *vm, t_cmd *cmd, int pos);
void				vm_winner(t_vm *vm);

int					vm_v_cmd(int a, int b, int c);
int					vm_direct(t_vm *vm, t_cmd *cmd, int *arg);
int					vm_indir(t_vm *vm, t_cmd *cmd, int nb);
int					get_indir_arg(t_vm *vm, t_cmd *cmd, int nb);
void				vm_rdr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_rrr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_idr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_iir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_dir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_ddr(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_drr(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_rir(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_irr(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_live(t_vm *vm, t_cmd *cmd);
void				vm_ld(t_vm *vm, t_cmd *cmd);
void				vm_st(t_vm *vm, t_cmd *cmd);
void				vm_add(t_vm *vm, t_cmd *cmd);
void				vm_sub(t_vm *vm, t_cmd *cmd);
void				vm_and(t_vm *vm, t_cmd *cmd);
void				vm_or(t_vm *vm, t_cmd *cmd);
void				vm_xor(t_vm *vm, t_cmd *cmd);
void				vm_zjmp(t_vm *vm, t_cmd *cmd);
void				vm_ldi(t_vm *vm, t_cmd *cmd);
int					vm_rid_sti(t_vm *vm, t_cmd *cmd);
int					vm_rrr_sti(t_vm *vm, t_cmd *cmd);
int					vm_rrd_sti(t_vm *vm, t_cmd *cmd);
int					vm_rir_sti(t_vm *vm, t_cmd *cmd);
int					vm_rdd_sti(t_vm *vm, t_cmd *cmd);
void				vm_sti(t_vm *vm, t_cmd *cmd);
void				vm_fork(t_vm *vm, t_cmd **cmd);
void				vm_lld(t_vm *vm, t_cmd *cmd);
void				vm_lldi(t_vm *vm, t_cmd *cmd);
void				vm_lfork(t_vm *vm, t_cmd **cmd);
void				vm_aff(t_vm *vm, t_cmd *cmd);
int 				get_reg(t_vm *vm, int *i);
int 				is_reg(int value);
int					vm_getpl(t_vm *vm, int place);

void				vm_load_ncurses(void);
void				vm_vis_arena(t_vm *vm);
void				print_logo(int j, t_vm *vm);
void				vm_n_draw_win(int j, int pl);
void				draw_pl_heart(int j, t_vm *vm);
int					vm_vis_winner(t_vm *vm);

#endif
