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
# include "curses.h"
/*
**					[Macros for ERROR MANAGER]
*/
# define ERR_NBR_INV	0
# define ERR_NO_NBR		1
# define ERR_NO_CHMP	2
# define ERR_NBR_CHMP	3
# define ERR_CMP_CHMP	4

#define IND_SIZE 2
#define REG_SIZE 4
#define DIR_SIZE REG_SIZE

#define REG_CODE 1
#define DIR_CODE 2
#define IND_CODE 3

#define MAX_ARGS_NUMBER 4
#define MAX_PLAYERS 4
#define MEM_SIZE (4 * 1024)
#define IDX_MOD (MEM_SIZE / 8)
#define CHAMP_MAX_SIZE (MEM_SIZE / 6)

#define COMMENT_CHAR '#'
#define COMMENT_CHAR2 ';'
#define LABEL_CHAR ':'
#define DIRECT_CHAR '%'
#define SEPARATOR_CHAR ','

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

typedef struct 		s_cmd
{
	int				reg[REG_NUMBER];
	int				pl;
	int				idx;
	int				rgb;
	int				playing;
	int				wait;
	int				off;
	int				carry;
	int				life;
	int				nbr_process;
	int				flag;
	int				on;
	int				lnew;
	int				zero;
	int				overlap;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_arena
{
	char			acb;
	int				overlap;
	int				pl;
	int				rgb;
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
	int				nbr_process;
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
	int				lifes;
	int				total_process;
	int				total_cycle;
	int				win;
	int				aff;
	int				debug;
	int				visual;
	int				show_live;
	int				on;
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

extern t_op			g_op_tab[17];

int					vm_usage(void);
int					vm_param_n(t_vm *vm, char **av, int *i, int ac);
int					vm_isnumber(char *str);
int					vm_get_param(char **av, t_vm *vm, int ac);
void				vm_champs(t_vm *vm, char *arg);
void				vm_init(t_vm *vm);
void				vm_create_arena(t_vm *vm);
void				vm_load_lists(t_cmd **cmd, t_vm *vm);
void				vm_glow_cur(t_vm *vm, t_cmd *cmd);
void				vm_dump_arena(t_vm *vm);
void				vm_create_arena(t_vm *vm);
void				vm_load_arena(t_vm *vm);
void				vm_cmd_triger(t_vm *vm, t_cmd *cmd, int hex);
void				vm_cycler_to_die(t_vm *vm, int *i);
void				vm_set_cycle_wait(t_vm *vm, t_cmd *cmd);
void				vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd);
int					vm_cmd(t_vm *vm, t_cmd *cmd, int chk);
int					vm_dia(int nb);
int					vm_its_cmd(t_vm *vm, t_cmd *cmd);
void				vm_load_champs(t_vm *vm);
void				vm_read_champ(t_vm *vm, int nbr_player, int size);
void				vm_dump_arena(t_vm *vm);
void				vm_exit(t_vm *vm);

void				display_header(void);
void				vm_err_exit(t_vm *vm, int error);
char				*vm_str_error(int error);
void				free_vm(t_vm *vm);
void				vm_exit(t_vm *vm);

int					mdx(int nbr);
int					vm_pos_curs(t_vm *vm, t_cmd *cmd);
void				vm_next_step(t_vm *vm, t_cmd *cmd, int pos);
void				vm_winner(t_vm *vm);

int					vm_v_cmd(int a, int b, int c);
int					vm_ffdir(t_vm *vm, t_cmd *cmd, int *arg);
int					vm_indir(t_vm *vm, t_cmd *cmd, int nb);
int					get_indir_arg(t_vm *vm, t_cmd *cmd, int nb);
void				vm_rdr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_rrr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_idr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_iir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_dir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_ddr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_drr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_rir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_irr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_live(t_vm *vm, t_cmd *cmd);
void				vm_ld(t_vm *vm, t_cmd *cmd, int x);
void				vm_st(t_vm *vm, t_cmd *cmd, int x);
void				vm_add(t_vm *vm, t_cmd *cmd, int x);
void				vm_sub(t_vm *vm, t_cmd *cmd, int x);
void				vm_and(t_vm *vm, t_cmd *cmd, int x);
void				vm_or(t_vm *vm, t_cmd *cmd, int x);
void				vm_xor(t_vm *vm, t_cmd *cmd, int x);
void				vm_zjmp(t_vm *vm, t_cmd *cmd);
void				vm_ldi(t_vm *vm, t_cmd *cmd, int x);
void				vm_ldi_idr_ddr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_ldi_irr_drr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_ldi_rdr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_ldi_next(t_vm *vm, t_cmd *cmd, int x, int hex);
int					vm_rid_sti(t_vm *vm, t_cmd *cmd);
int					vm_rrr_sti(t_vm *vm, t_cmd *cmd);
int					vm_rrd_sti(t_vm *vm, t_cmd *cmd);
int					vm_rir_sti(t_vm *vm, t_cmd *cmd);
int					vm_rdd_sti(t_vm *vm, t_cmd *cmd);
void				vm_sti(t_vm *vm, t_cmd *cmd, int x);
void				vm_fork(t_vm *vm, t_cmd **cmd);
void				vm_lld(t_vm *vm, t_cmd *cmd, int x);
void				vm_lldi(t_vm *vm, t_cmd *cmd, int x);
void				lldi_idr_ddr(t_vm *vm, t_cmd *cmd, int hex);
void				lldi_irr_drr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_lldi_rdr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_lldi_next(t_vm *vm, t_cmd *cmd, int x, int hex);
void				vm_lfork(t_vm *vm, t_cmd **cmd);
void				vm_aff(t_vm *vm, t_cmd *cmd, int x);
int 				get_reg(t_vm *vm, int *i);
int 				is_reg(int value);
int					vm_getpl(t_vm *vm, int place);
int					vm_new_step(t_vm *vm, t_cmd *cmd, int run);
int					vm_len_step(t_vm *vm, t_cmd *cmd, int idx);

void				vm_load_ncurses(void);
void				vm_vis_arena(t_vm *vm);
void				vm_game_stat(t_vm *vm, int j);
void				print_logo(int j, t_vm *vm);
void				vm_n_draw_win(int j, int pl);
void				draw_pl_heart(int pl, int j, t_vm *vm);
int					vm_vis_winner(t_vm *vm);

#endif
