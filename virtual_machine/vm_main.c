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


void	vm_play_arena(t_vm *vm)
{
	int	i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		printw(" ");
		attron(COLOR_PAIR(vm->arena[i].rgb));
		printw("%02x", 0xFF & vm->arena[i].acb);
		if ((i + 1) % 64 == 0)
		{ 
			//mem += 64;
			//if (i + 1 < MEM_SIZE)			
				printw(" \n");
		}		
		i++;		
	}
	printw("\n");
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
		i++;
	}
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
		while (c)
		{
			vm_play_arena(vm);
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
		lst->on = 0;
		lst->off = 0;
		lst->carry = 0;
		lst->wait = 0;
		lst->increment = 0;
		lst->playing = 0;
		lst->next = NULL;
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
