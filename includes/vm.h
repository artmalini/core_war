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
# include <ncurses.h>
#define IND_SIZE 2
#define REG_SIZE 4
#define DIR_SIZE REG_SIZE


#define REG_CODE 1
#define DIR_CODE 2
#define IND_CODE 3


#define MAX_ARGS_NUMBER 4
#define MAX_PLAYERS 4
#define MEM_SIZE (4 * 1024)
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

// typedef struct		s_header
// {
// 	unsigned int	magic;
// 	char			prog_name [PROG_NAME_LENGTH + 1];
// 	unsigned int	prog_size;
// 	char			how [COMMENT_LENGTH + 1];
// }					t_header;

# define BUF_SIZE (5)

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

typedef struct		s_arena
{
	char	acb;
}					t_arena;

typedef struct		s_champ
{
	int				id;
	char			*name;
	char			comment[COMMENT_LENGTH];
	int				magic_number;
	int				weight;
	char			*prog;

}					t_champ;

typedef struct		s_vm
{
	int				fd;
	int				dump_cycle;
	t_champ			tab_champ[MAX_PLAYERS];
	int				nbr_next;
	//unsigned char	arena[MEM_SIZE];
	t_arena			arena[MEM_SIZE];
	int				cycle;
	int				last_check;
	int				cycle_to_die;
	int				cycle_before_checking;
	int				total_lives_period;
}					t_vm;

int			vm_usage(void);
int			vm_param_n(t_vm *vm, char **av, int *i, int ac);
int			ft_isnumber(char *str);
int			vm_get_param(char **av, t_vm *vm, int ac);
void		vm_dump_arena(t_vm *vm);
void		vm_create_arena(t_vm *vm);
void		vm_load_champs(t_vm *vm);
void		vm_read_champ(t_vm *vm, int number_player);

#endif