/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:06:48 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/06 11:06:49 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*void	vm_dump_arena(t_vm *vm)
{
	int	i;
	int	mem;

	mem = 64;
	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != MEM_SIZE && i != 0 && i != 64)
		{
			ft_printf("\n");
			ft_printf("%#06x : ", mem);
			ft_printf("%02x ", 0xFF & vm->arena[i].acb);
			mem += 64;
		}
		else if (i == 64)
		{
			ft_printf("\n");
			ft_printf("%#06x : ", mem);
			mem += 64;
		}
		ft_printf("%02x ", 0xFF &  vm->arena[i].acb);
		i++;
	}
	ft_printf("\n");
}*/

void	vm_dump_arena(t_vm *vm)
{
	int	i;
	int	mem;

	mem = 64;
	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", 0xFF & vm->arena[i].acb);
		if ((i + 1) % 64 == 0)
		{ 
			mem += 64;
			if (i + 1 < MEM_SIZE)
			{
				ft_printf("\n");
				ft_printf("%#06x : ", mem);
			}
		}
		i++;
	}
	ft_printf("\n");
}

void	vm_load_ncurses(void)
{
	initscr();
	noecho();
	start_color();
	init_color(COLOR_WHITE, 200, 0, 0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_pair(5, COLOR_WHITE, COLOR_RED);
	init_pair(6, COLOR_WHITE, COLOR_YELLOW);
	init_pair(7, COLOR_WHITE, COLOR_GREEN);
	init_pair(8, COLOR_WHITE, COLOR_CYAN);

	init_pair(9, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(11, COLOR_WHITE, COLOR_BLACK);
	curs_set(FALSE);
}

void	vm_game_stat(t_vm *vm)
{
	attron(COLOR_PAIR(10));
	printw("Cycle : %d Cycles to die: %d\n", vm->cycle, vm->cycle_to_die);
	refresh();
}


void	vm_play_arena(t_vm *vm)
{
	int	i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		//printw(" ");
		attron(COLOR_PAIR(vm->arena[i].rgb));
		printw("%02x ", 0xFF & vm->arena[i].acb);
		if ((i + 1) % 64 == 0)
		{ 
			//mem += 64;
			//if (i + 1 < MEM_SIZE)			
				printw(" \n");
		}		
		i++;		
	}
	printw("\n");
	vm_game_stat(vm);
	refresh();
	
}

void	vm_create_arena(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i].acb = 0;
		vm->arena[i].rgb = 11;
		vm->arena[i].asc_rgb = 11;
		vm->arena[i].flag = 0;
		i++;
	}
}








int		vm_has_cmd(t_vm *vm, t_cmd *cmd)
{
	int i;

	i = vm->arena[cmd->idx].acb & 0xFF;
	// erase();
	// attron(COLOR_PAIR(11));
	// printw("vm_has_cmd |%d|\n", i);
	// refresh();
	if (i > 0 && i < 17)
		return (i);
	else
		return (0);
}

void	vm_next_step(t_vm *vm, t_cmd *cmd, int pos)
{
	int		i;
	int		tm;

	if (vm->arena[cmd->idx].flag > 0)
		vm->arena[cmd->idx].flag--;
	tm = cmd->idx;
 	i = cmd->idx + pos;
	cmd->idx = i % MEM_SIZE < 0 ? i % MEM_SIZE + MEM_SIZE : i % MEM_SIZE;
	
		// erase();
		// attron(COLOR_PAIR(11));
		 printw("vm_next_step |%d|\n", vm->arena[cmd->idx].flag);
		 refresh();
	vm->arena[cmd->idx].flag++;
	vm->arena[cmd->idx].rgb = cmd->rgb;
	if (vm->arena[tm].flag == 0)
		vm->arena[tm].rgb = vm->arena[tm].asc_rgb;
	
}






















void	vm_curet_next(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->on)
			cmd->off = 1;
		cmd->on = 0;
		cmd = cmd->next;
	}
}

void	vm_cycler_todie(t_vm *vm, t_cmd *cmd, int *i)
{
	vm_curet_next(cmd);
	if (vm->lives == 0 || (vm->cycle_to_die - CYCLE_DELTA) < 1)
		*i = 0;
	if (vm->lives < NBR_LIVE)
		vm->last_check += 1;
	if (vm->last_check == MAX_CHECKS || vm->lives >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->cycle_to_die < 0)
			vm->cycle_to_die = 0;
		vm->lives = 0;
		vm->last_check = 0;
	}
	vm->cycle = 0;
}

void	vm_cycler_to_die(t_vm *vm, t_cmd *cmd, int *i)
{
	if (vm->cycle == vm->cycle_to_die)
		vm_cycler_todie(vm, cmd, i);
	//	vm_switch_cursor(cmd);
	else
	{
		vm->cycle++;
	}
	//cmd = cmd->next;
	//vm_play_arena(vm);
}

void	vm_set_cycle_wait(t_vm *vm, t_cmd *cmd)
{
	int		i;

	if ((i = vm_has_cmd(vm, cmd)) != 0)
	{
		cmd->playing = 1;		
		cmd->wait = op_tab[i].cycles;
		//vm_next_step(vm, cmd, 1);
		//
		//printw("%d\n", op_tab[i].cycles);
		//refresh();
	}
	else
		vm_next_step(vm, cmd, 1);
}

int		vm_step_shift(int type, int label_size)
{
	if (type == REG_CODE)
		return (1);
	else if (type == DIR_CODE)
		return (2 + 2 * (1 - label_size));
	else if (type == IND_CODE)
		return (2);
	else
		return (0);
}

int		vm_calc_steps(int hex, int pos)
{
	int		param;
	int		ret;

	ret = 0;
	param = (op_tab[hex].nbr_args);
			//printw("param |%d|\n", param);
			//refresh();
	if (hex < 1 || hex > 16)
		return (1);
	ret = vm_step_shift((pos >> 6) & 3, op_tab[hex].size);	
	if (param > 1)
		ret += vm_step_shift((pos >> 4) & 3, op_tab[hex].size);
	if (param > 2)
		ret += vm_step_shift((pos >> 2) & 3, op_tab[hex].size);
			//printw("ret |%d|\n", ret);
			//refresh();	
	return (ret + 2);
}

void	vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		pos;
	int		hex;

	if (cmd->wait == 0)
	{
		hex = vm->arena[cmd->idx].acb;
		pos = vm->arena[cmd->idx + 1].acb;
		vm_next_step(vm, cmd, vm_calc_steps(hex, pos));		
			//printw("%d %d\n", pos, hex);
			//refresh();		
		cmd->playing = 0;
	}
	else
		cmd->wait -= 1;
}

void	vm_load_arena(t_vm *vm)
{
	int		i;
	t_cmd	*c;


	i = 1;
	vm_load_ncurses();

	//vm_dump_arena(vm);
	//while (++i < 2)
	//	vm_play_arena(vm);
	while (i)
	{		
		c = vm->cmd;
		vm_play_arena(vm);		
		while (c)
		{
			vm_cycler_to_die(vm, c, &i);
			if (!c->off)
			{
				if (!c->playing)
				{
					vm_set_cycle_wait(vm, c);
					//vm_play_arena(vm);
				//printw("%d\n", c->wait);
				//refresh();				
				}
				else
					vm_run_waiting_cycle(vm, c);
			}

			//printw("%d\n", c->wait);
			//refresh();
			c = c->next;
		}
	}
	
	getch();
	endwin();
}

static void	free_vm(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < vm->nbr_next)
	{
		free(vm->tab_champ[i].name);
		free(vm->tab_champ[i].prog);
		i++;
	}
	free(vm);
}

static void	init(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->tab_champ[i].weight = 0;
		vm->tab_champ[i].id = -1;
		i++;
	}
	vm->fd = 0;
	vm->dump_cycle = -1;
	vm->nbr_next = 0;
	vm->cycle = 0;
	vm->last_check = 0;
	vm->total_lives_period = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_before_checking = CYCLE_TO_DIE;
	vm->lives = 0;
	vm->cmd = NULL;
}

t_cmd		*add_list(t_vm *vm, int i)
{
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		lst->reg[0] = vm->tab_champ[i].id;
		lst->idx = vm->tab_champ[i].idx;//индекс первой  позиции курсора
		lst->rgb = 5 + (i % 4);//цвет каретки		
		lst->playing = 0;
		lst->wait = 0;
		lst->on = 0;
		lst->off = 0;
		lst->carry = 0;
		lst->increment = 0;
		lst->next = NULL;
		//ft_printf("lst->idx |%d\n|", lst->idx);
	}	
	return (lst);
}

void	vm_load_lists(t_cmd **cmd, t_vm *vm)
{
	int		i;
	t_cmd	*tmp;

	tmp = *cmd;
	i = -1;	
	while (++i < vm->nbr_next)
	{
		if (tmp)
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = add_list(vm, i);
		}
		else
			*cmd = add_list(vm, i);
		ft_printf("@@@ %d %d\n", vm->tab_champ[i].id, vm->tab_champ[i].idx);
	}
}

int			main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc < 2)
		vm_usage();
	vm = ft_memalloc(sizeof(t_vm));
	vm->last_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	init(vm);
	vm_create_arena(vm);
	if (vm_get_param(argv, vm, argc) == 0)
		vm_usage();
	vm_load_champs(vm);
	vm_load_lists(&vm->cmd, vm);
	//нужно дописать функцию самой игры и реализовать функции
	vm_load_arena(vm);
	ft_printf("main vm->tab_champ[0].weight %d\n", vm->tab_champ[0].weight);
	free_vm(vm);
	return (0);
}

// int main() {

//  initscr();
//  noecho();
//  curs_set(FALSE);

//  mvprintw(0, 0, "Hello, world!");
//  refresh();

//  sleep(1);

//  endwin();
// }



// // void vm_read(char *av, int fd)
// // {
// // 	char *
// // }

// int main(int argc, char **argv)
// {
// 	int fd;
// 	int ret;
// 	//int i;
// 	//char buf[BUF_SIZE];
// 	char *line;
// 	//t_player p;

// 	if (argc == 1)
// 		ft_error("Not enough arguments.");
// 	//i = 0;
// 	//ft_bzero(&p, sizeof(t_player));
// 	line = ft_memalloc(CHAMP_MAX_SIZE);
// 	fd = open(argv[1], O_RDONLY);
// 	while ((ret = read(fd, line, CHAMP_MAX_SIZE)) > 0)
// 	{
// 		line[ret] = '\0';
// 		ft_printf("%s", line);
// 	}
// 	ft_memdel((void**)&line);
// 	return (0);
// }

/*int main(int argc, char **argv)
{
	int fd;
	int ret;
	//int i;
	//char buf[BUF_SIZE];
	char *line;
	//t_player p;

	if (argc == 1)
		ft_error("Not enough arguments.");
	//i = 0;
	//ft_bzero(&p, sizeof(t_player));
	line = ft_memalloc(CHAMP_MAX_SIZE);
	fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, line, CHAMP_MAX_SIZE)) > 0)
	{
		line[ret] = '\0';
		ft_printf("%s\n", line);
		// if (i <= 1)
		// 	p.magic = ft_strjoin(p.magic, ft_strsub(buf, 0, BUF_SIZE));
		// else if (i <= PROG_NAME_LENGTH / 2 + 2)
		// 	p.bot_name = ft_strjoin(p.bot_name, ft_strsub(buf, 0, BUF_SIZE));
		// else if (i == PROG_NAME_LENGTH / 2 + 4)
		// 	p.size_exec = ft_atoi_base(buf, 16); //здесь должно быть переведение з 16 в 10 систему, но пока просто атои
		// else if (i <= PROG_NAME_LENGTH / 2 + 4 + COMMENT_LENGTH / 2)
		// 	p.comment = ft_strjoin(p.comment, ft_strsub(buf, 0, BUF_SIZE));
		// else if (i >  PROG_NAME_LENGTH / 2 + 4 + COMMENT_LENGTH / 2 + 1)
		// 	p.ex_code = ft_strjoin(p.ex_code, ft_strsub(buf, 0, BUF_SIZE));
		// i++;
	}
	ft_memdel((void**)&line);
	return (0);
}*/
