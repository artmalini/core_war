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
	vm_glow_cur(vm, vm->cmd);
	//нужно дописать функцию самой игры и реализовать функции
	vm_load_arena(vm);
	//ft_printf("main vm->tab_champ[0].weight %d\n", vm->tab_champ[0].weight);
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


/*void	check_process(t_vm *vm)
{
	t_cmd	*tmp;
	//int		i;

	tmp = vm->cmd;
	//i = vm->total_process - 1;
	//printf("total_process|%d\n", i);
	// while (tmp && !tmp->flag)
	// {
	// 	if (!tmp->life)
	// 	{
	// 		//ft_printf("OK\n");
	// 		tmp->off = 1;
	// 		tmp->flag = 1;
	// 		vm->tab_champ[tmp->reg[0]].nbr_process -= 1;
	// 	}
	// 	tmp = tmp->next;
	// }
}*/

/*void	vm_curet_next(t_vm *vm, t_cmd *cmd)
{
	//printf("total_process|%d\n", cmd->life);
	while (cmd && !cmd->flag)
	{
		if (!vm->tab_champ[cmd->reg[0]].alive)
		{
			//ft_printf("yepnext\n");
			vm->tab_champ[cmd->reg[0]].nbr_process -= 1;
			cmd->off = 1;
			cmd->flag = 1;
		}
		cmd->life = 0;
		cmd = cmd->next;
	}
}

void	vm_cycler_todie(t_vm *vm, t_cmd *cmd, int *i)
{

	//ft_printf("cmd->reg[0] %d\n", vm->tab_champ[cmd->reg[0]].old_check);
	if (vm->lifes == 0 || (vm->cycle_to_die - CYCLE_DELTA) < 1)
		*i = 0;
	if (vm->tab_champ[cmd->reg[0]].alive < NBR_LIVE)
		vm->tab_champ[cmd->reg[0]].old_check += 1;
	if (vm->tab_champ[cmd->reg[0]].old_check == MAX_CHECKS || vm->tab_champ[cmd->reg[0]].alive >= NBR_LIVE)
	{
			//check_process(vm);
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->cycle_to_die < 0)
		{
			//vm_curet_next(vm, cmd);
			//vm->tab_champ[cmd->reg[0]].nbr_process -= 1;
			vm->cycle_to_die = 0;
			//vm->tab_champ[cmd->reg[0]].old_check = 0;
		}
		vm->tab_champ[cmd->reg[0]].alive = 0;
		vm->tab_champ[cmd->reg[0]].old_check = 0;
	}
	vm->cycle = 0;
	//vm->lifes = 0;
}*/


/*void	vm_curet_next(t_cmd *cmd)
{
	while (cmd && !cmd->flag)
	{
		if (!cmd->life)
		{
			cmd->off = 1;
			cmd->flag = 1;
		}
		cmd->life = 0;
			//printw("cmd->reg[0] %d\n", cmd->reg[0]);
			//refresh();
		cmd = cmd->next;
	}
}

void	vm_cycler_todie(t_vm *vm, t_cmd *cmd, int *i)
{
	vm_curet_next(cmd);
	if (vm->lifes == 0 || (vm->cycle_to_die - CYCLE_DELTA) < 1)
		*i = 0;
	if (vm->lifes < NBR_LIVE)
		vm->last_check += 1;
	if (vm->last_check == MAX_CHECKS || vm->lifes >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->cycle_to_die < 0)
		{
			//vm_curet_next(cmd);
			vm->cycle_to_die = 0;
		}
		vm->lifes = 0;
		vm->last_check = 0;
	}
	vm->cycle = 0;
	//vm->lives = 0;
}*/
