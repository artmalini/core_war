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

# include "op.h"
# include "color.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
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

typedef struct		s_error
{
	int				id;
	char			*name;

}					t_error;

typedef struct 		s_cmd
{
	int				reg[REG_NUMBER];
	int				idx;
	int				rgb;
	int				on;
	int				off;
	int				carry;
	int				wait;
	int				playing;
	int				flag;
	int				life;	
	int				nbr_process;
	struct s_cmd	*next;
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
	int				rgb;//main color for chars on arena
	int				asc_rgb;
	int				flag;
	//int				bold;	
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
}					t_vm;

/*
**					[MAIN FUNCTIONS]
*/

int					vm_its_cmd(t_vm *vm, t_cmd *cmd);
void				vm_read_champ(t_vm *vm, int nbr_player);
void				vm_cmd_triger(t_vm *vm, t_cmd *cmd, int hex);

/*
**					[MAIN COMMANDS]
*/

void				vm_ld(t_vm *vm, t_cmd *cmd);
void				vm_st(t_vm *vm, t_cmd *cmd);
void				vm_or(t_vm *vm, t_cmd *cmd);
void				vm_and(t_vm *vm, t_cmd *cmd);
void				vm_add(t_vm *vm, t_cmd *cmd);
void				vm_aff(t_vm *vm, t_cmd *cmd);
void				vm_xor(t_vm *vm, t_cmd *cmd);
void				vm_sub(t_vm *vm, t_cmd *cmd);
void				vm_lld(t_vm *vm, t_cmd *cmd);
void				vm_zjmp(t_vm *vm, t_cmd *cmd);
void				vm_live(t_vm *vm, t_cmd *cmd);
void				vm_fork(t_vm *vm, t_cmd **cmd);
void				vm_lfork(t_vm *vm, t_cmd **cmd);

/*
**					[vm_arena.c]
*/

void				vm_load_arena(t_vm *vm);
void				vm_play_arena(t_vm *vm);
void				vm_create_arena(t_vm *vm);
void				vm_glow_cur(t_vm *vm, t_cmd *cmd);
void				vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd);

/*
**					[vm_cycles.c]
*/

void				vm_curet_next(t_cmd *cmd);
void				pl_period_live(t_vm *vm);
int					vm_has_cmd(t_vm *vm, t_cmd *cmd);
void				vm_cycler_todie(t_vm *vm, int *i);
void				vm_cycler_to_die(t_vm *vm, int *i);
void				vm_set_cycle_wait(t_vm *vm, t_cmd *cmd);

/*
**					[vm_ldi.c]
*/

void				vm_ldi(t_vm *vm, t_cmd *cmd);
void				vm_ldi_rdr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_irr_drr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_idr_ddr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_ldi_write(t_vm *vm, t_cmd *cmd, int val, int i);

/*
**					[vm_lldi.c]
*/

void				vm_lldi(t_vm *vm, t_cmd *cmd);
void				vm_lldi_rdr(t_vm *vm, t_cmd *cmd, int hex);
void				lldi_irr_drr(t_vm *vm, t_cmd *cmd, int hex);
void				lldi_idr_ddr(t_vm *vm, t_cmd *cmd, int hex);
void				vm_lldi_write(t_vm *vm, t_cmd *cmd, int val, int i);

/*
**					[vm_load.c]
*/

void				vm_load_champs(t_vm *vm);
void				load_champ_to(t_vm *vm, t_champ champ, int memory_index, int num_pl);

/*
**					[vm_lst.c]
*/

t_cmd				*add_list(t_vm *vm, int i);
void				vm_load_lists(t_cmd **cmd, t_vm *vm);

/*
**					[vm_mng.c]
*/

int					mdx(int nbr);
int					vm_v_cmd(int a, int b, int c);
int					vm_pos_curs(t_vm *vm, t_cmd *cmd);
int					vm_indir(t_vm *vm, t_cmd *cmd, int nb);
int					vm_direct(t_vm *vm, t_cmd *cmd, int *arg);
void				vm_rrr_bit(t_cmd *cmd, int *arg, int let);
int					get_indir_arg(t_vm *vm, t_cmd *cmd, int nb);
void				vm_ddr(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_drr(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_rir(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_irr(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_rdr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_idr_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_iir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);
void				vm_dir_bit(t_vm *vm, t_cmd *cmd, int *arg, int let);

/*
**					[vm_ncurses.c]
*/

void				vm_load_ncurses(void);
void				vm_game_stat(t_vm *vm);
void				vm_pl_stats(t_vm *vm, int i);

/*
**					[vm_params.c]
*/

int					ft_isnumber(char *str);
void				champs(t_vm *vm, char *arg);
int					vm_get_param(char **av, t_vm *vm, int ac);
int					vm_param_n(t_vm *vm, char **av, int *i, int ac);

/*
**					[vm_steps.c]
*/

int					vm_calc_steps(int hex, int pos);
int					vm_step_shift(int type, int label_size);
void				vm_next_step(t_vm *vm, t_cmd *cmd, int pos);

/*
**					[vm_sti.c]
*/

void				vm_sti(t_vm *vm, t_cmd *cmd);
int					vm_rid_sti(t_vm *vm, t_cmd *cmd);
int					vm_rrr_sti(t_vm *vm, t_cmd *cmd);
int					vm_rrd_sti(t_vm *vm, t_cmd *cmd);
int					vm_rir_sti(t_vm *vm, t_cmd *cmd);
int					vm_rdd_sti(t_vm *vm, t_cmd *cmd);
void				load_res(t_vm *vm, t_cmd *cmd, int direct);

/*
**					[DEBUG and PRINT and ERROR]
*/

int					vm_usage(void);
//void				draw_dead_pl(int j);
void				draw_pl_heart(int j);
void				vm_dump_arena(t_vm *vm);
char				*vm_str_error(int error);
void				ft_print_error(t_error *e);
void				print_header(int j, t_vm *vm);
void				print_header2(int j, t_vm *vm);

/*
**					[vm_free_and_init.c]
*/

void				init(t_vm *vm);
void				free_vm(t_vm *vm);

#endif

/*
**					[vm_and1.c]
*/

//int					mod(int a, int b);
//int					get_ind(t_vm *vm, int *i);
//void				and(t_vm *vm, t_proc *proc);
//long int			get_value(t_vm *vm, int index);
//static void			choose_op(int *arg, t_proc *proc);
//int					get_dir(t_vm *vm, int *i, int op_code);
//void				param_op(t_vm *vm, t_proc *proc, int *arg);
//static void			param_op_2(t_vm *vm, t_proc *proc, int *arg, int *pc);

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