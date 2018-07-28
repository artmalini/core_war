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
	//init_color(COLOR_RED, 68, 0, 0);
	//init_pair(0, COLOR_WHITE, COLOR_BLACK);
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

void	vm_pl_stats(t_vm *vm, int i)
{
	attron(COLOR_PAIR(vm->tab_champ[i].rgb));
	printw("\nLives for %.20s	%d Process: %d", vm->tab_champ[i].name, vm->tab_champ[i].prev_live, vm->tab_champ[i].nbr_process);
	printw(" Lives in current period: %d", vm->tab_champ[i].lives_in_period);
	printw("\t\t Total cycles: %d", vm->total_cycle);
}

void	vm_game_stat(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->nbr_next)
		vm_pl_stats(vm, i);
	attron(COLOR_PAIR(10));
	printw("\nCycle : %d Cycles to die: %d \n\n", vm->cycle, vm->cycle_to_die);
}

void	vm_winner(t_vm *vm)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (++i < vm->nbr_next)
	{
		if (vm->tab_champ[i].prev_live > vm->tab_champ[j].prev_live)
			j = i;
	}
	if (vm->debug)
		ft_printf("Contestant %d, \"%s\", has won !\n", vm->tab_champ[j].id, vm->tab_champ[j].name);
}

int		vm_vis_winner(t_vm *vm)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (++i < vm->nbr_next)
	{
		if (vm->tab_champ[i].prev_live > vm->tab_champ[j].prev_live)
			j = i;
	}
	return (j);
}

// void	draw_dead_pl(int j)
// {
// ##  ### ##  
// # #  #  # # 
// ##   #  ##  
// # #  #  #   
// # # ### #
// }

void	draw_winner(int j, t_vm *vm)
{
// #     # ### #    # 
// #  #  #  #  ##   # 
// #  #  #  #  # #  # 
// #  #  #  #  #  # # 
//  ## ##  ### #   ## 
	int		pl;

	pl = vm_vis_winner(vm);
	attron(COLOR_PAIR(1));
	if (vm->cycle_to_die == 0 && vm->total_cycle != 0)
	{
		if (pl == 0)
		{
			if (j == 21)
				printw("\t #     # ### #    #");
			if (j == 22)
				printw("\t #  #  #  #  ##   #");
			if (j == 23)
				printw("\t #  #  #  #  # #  #");
			if (j == 24)
				printw("\t #  #  #  #  #  # #");
			if (j == 25)
				printw("\t  ## ##  ### #   ##");
		}
		if (pl == 1)
		{
			if (j == 27)
				printw("\t #     # ### #    #");
			if (j == 28)
				printw("\t #  #  #  #  ##   #");
			if (j == 29)
				printw("\t #  #  #  #  # #  #");
			if (j == 30)
				printw("\t #  #  #  #  #  # #");
			if (j == 31)
				printw("\t  ## ##  ### #   ##");
		}
		if (pl == 2)
		{
			if (j == 33)
				printw("\t #     # ### #    #");
			if (j == 34)
				printw("\t #  #  #  #  ##   #");
			if (j == 35)
				printw("\t #  #  #  #  # #  #");
			if (j == 36)
				printw("\t #  #  #  #  #  # #");
			if (j == 37)
				printw("\t  ## ##  ### #   ##");
		}
		if (pl == 3)
		{
			if (j == 39)
				printw("\t #     # ### #    #");
			if (j == 40)
				printw("\t #  #  #  #  ##   #");
			if (j == 41)
				printw("\t #  #  #  #  # #  #");
			if (j == 42)
				printw("\t #  #  #  #  #  # #");
			if (j == 43)
				printw("\t  ## ##  ### #   ##");
		}
	}
}


void	draw_pl_heart(int j, t_vm *vm)
{
	attron(COLOR_PAIR(1));
	if (vm->cycle_to_die > 0)
	{
		if (j == 21 || j == 27 || j == 33 || j == 39)
			printw("\t ###    ###");
		if (j == 22 || j == 28 || j == 34 || j == 40)
			printw("\t#####  #####");
		if (j == 23 || j == 29 || j == 35 || j == 41)
			printw("\t ##########");
		if (j == 24 || j == 30 || j == 36 || j == 42)
			printw("\t   ######");
		if (j == 25 || j == 31 || j == 37 || j == 43)
			printw("\t     ##");
	}
	else
		draw_winner(j, vm);
}

void	print_header2(int j, t_vm *vm)
{
	if (j == 13)
		printw(" #############   ####  ############ ");
	if (j == 14)
		printw(" ###### ######  ####   ###### ####  ");
	if (j == 15)
		printw(" #####   ##### ##############  #### ");
	if (j == 16)
		printw(" ####     ########     ######   #### ");
	if (j >= 20 && j <= 25 && vm->nbr_next >= 1)
	{
		if (j == 20)
		{
			attron(COLOR_PAIR(vm->tab_champ[0].rgb));
			printw("%.16s", vm->tab_champ[0].name);
		}
		draw_pl_heart(j, vm);
	}
	if (j >= 26 && j <= 31 && vm->nbr_next >= 2)
	{
		if (j == 26)
		{
			attron(COLOR_PAIR(vm->tab_champ[1].rgb));
			printw("%.16s", vm->tab_champ[1].name);
		}
		draw_pl_heart(j, vm);
	}
	if (j >= 32 && j <= 37 && vm->nbr_next >= 3)
	{
		if (j == 32)
		{
			attron(COLOR_PAIR(vm->tab_champ[2].rgb));
			printw("%.16s", vm->tab_champ[2].name);
		}
		draw_pl_heart(j, vm);
	}
	if (j >= 38 && j <= 43 && vm->nbr_next == 4)
	{
		if (j == 38)
		{
			attron(COLOR_PAIR(vm->tab_champ[3].rgb));
			printw("%.16s", vm->tab_champ[3].name);
		}
		draw_pl_heart(j, vm);
	}
}

void	print_header(int j, t_vm *vm)
{
	if (j == 0)
		printw("  #######                 ##########");
	if (j == 1)
		printw(" ####  ###                ###       ");
	if (j == 2)
		printw(" ###    ##                ###       ");
	if (j == 3)
		printw(" ###         ##### ##############   ");
	if (j == 4)
		printw(" ###       ###  ## ####   ###       ");
	if (j == 5)
		printw(" ###    ######  ######    ###       ");
	if (j == 6)
		printw(" ####  ### ###  ## ###    ###       ");
	if (j == 7)
		printw("  #######    ####  ###    ##########");
	if (j == 9)
		printw(" ###       ###       ##############  ");
	if (j == 10)
		printw(" ###   #   ###      #########   #### ");
	if (j == 11)
		printw(" ###  ###  ###     ##########    ### ");
	if (j == 12)
		printw(" ### ##### ###    #### ######   #### ");
	print_header2(j, vm);	
}

void	vm_vis_arena(t_vm *vm)
{
	int	i;
	int	j;
	int	k;

	erase();
	i = 0;
	j = -1;
	k = 0;
	if (vm->cycle < 500)
		k = 1;
	else if (vm->cycle > 500 && vm->cycle < 800)
		k = 2;
	else if (vm->cycle > 800 && vm->cycle < 1000)
		k = 3;
	else
		k = 4;
	vm_game_stat(vm);
	while (i < MEM_SIZE)
	{
		//printw(" ");
		//if (vm->arena[i].bold > 0)
		//	attron(A_BOLD);
		attron(COLOR_PAIR(vm->arena[i].rgb));
		printw("%02x", 0xFF & vm->arena[i].acb);
		attroff(COLOR_PAIR(vm->arena[i].rgb));
		printw(" ");
		// if (vm->arena[i].bold > 0)
		// {
		// 	attroff(A_BOLD);
		// 	vm->arena[i].bold -= 1;
		// }
		if ((i + 1) % 64 == 0)
		{ 
			//mem += 64;
			//if (i + 1 < MEM_SIZE)
			attron(COLOR_PAIR(k));
			print_header(++j, vm);	
				printw("\n");
		}		
		i++;		
	}
	printw("\n");
	refresh();
}

void	vm_play_arena(t_vm *vm)
{
	if (vm->dump_cycle > -1)
	{
		if (vm->total_cycle == vm->dump_cycle)
			vm_dump_arena(vm);
	}
	else if (!vm->debug)
	{
		vm_vis_arena(vm);
	}	
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
		//vm->arena[i].bold = 0;
		vm->arena[i].o_acb = 0;
		vm->arena[i].hit = 0;
		vm->arena[i].pl = -666;
		i++;
	}
}

void	vm_cmd_triger2(t_vm *vm, t_cmd *cmd, int hex)
{
	if (hex == 12)
		vm_fork(vm, &cmd);
	else if (hex == 13)
		vm_lld(vm, cmd);
	else if (hex == 14)
		vm_lldi(vm, cmd);
	else if (hex == 15)
		vm_lfork(vm, &cmd);
	else if (hex == 16)
		vm_aff(vm, cmd);
	else
		return ;
}

void	vm_cmd_triger(t_vm *vm, t_cmd *cmd, int hex)
{
	if (hex == 1)
		vm_live(vm, cmd);
	else if (hex == 2)
		vm_ld(vm, cmd);
	else if (hex == 3)
		vm_st(vm, cmd);
	else if (hex == 4)
		vm_add(vm, cmd);
	else if (hex == 5)
		vm_sub(vm, cmd);
	else if (hex == 6)
		vm_and(vm, cmd);
	else if (hex == 7)
		vm_or(vm, cmd);
	else if (hex == 8)
		vm_xor(vm, cmd);
	else if (hex == 9)
		vm_zjmp(vm, cmd);
	else if (hex == 10)
		vm_ldi(vm, cmd);
	else if (hex == 11)
		vm_sti(vm, cmd);
	else
		vm_cmd_triger2(vm, cmd, hex);
}








void	vm_next_step(t_vm *vm, t_cmd *cmd, int pos)
{
	int		i;
	int		tm;

	if (vm->arena[cmd->idx].flag > 0)
		vm->arena[cmd->idx].flag--;
	tm = cmd->idx;
	i = cmd->idx + pos;
	//ft_printf("cmd->idx |%d|\n ", i);
	//if (cmd->on == 0)
	cmd->idx = (i % MEM_SIZE < 0) ? (i % MEM_SIZE + MEM_SIZE) : i % MEM_SIZE;
	//ft_printf("cmd->idx |%d| ", cmd->idx);
	//ft_printf("cmd->idx %d ", vm->arena[cmd->idx]);
	//refresh();
	// erase();
	// attron(COLOR_PAIR(11));
	// printw("vm_next_step |%d|\n", vm->arena[cmd->idx].flag);
	// refresh();
   // vm->arena[cmd->idx].pl = cmd->pl;
	vm->arena[cmd->idx].flag++;
	vm->arena[cmd->idx].rgb = cmd->rgb;
	if (vm->arena[tm].flag == 0)
		vm->arena[tm].rgb = vm->arena[tm].asc_rgb;
	
}














void	pl_period_live(t_vm *vm)
{
	int i;

	i = -1;
	while (++i < vm->nbr_next)
		vm->tab_champ[i].lives_in_period = 0;
}




/*int		vm_its_cmd(t_vm *vm, t_cmd *cmd)
{
	int		i;
	// int		a;
	// int 	b;


	////vm->arena[cmd->idx].pl = cmd->pl;
	i = 0;
	// if (vm->arena[mdx(cmd->idx)].hit == 1)
	// {
	// 	if (a != b)
 //        {
 //            if ((b - 1 >= 0 && b - 1 < 16) && (vm->arena[cmd->idx].pl != cmd->pl))
	// 		    vm->arena[mdx(cmd->idx)].acb = vm->arena[mdx(cmd->idx)].o_acb;
 //        }
	// }
		i = (vm->arena[mdx(cmd->idx)].acb & 0xFF) - 1;
	if (i < 0 || i > 16)
		return (0);
	else		
		return (1);	
}*/

int		vm_its_cmd2(t_vm *vm, t_cmd *cmd)
{
	int		i;

	i = (vm->arena[mdx(cmd->idx)].acb & 0xFF) - 1;
	if (i < 0 || i > 16)
		return (0);
	else
		return (1);
}


void	vm_curet_next(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->life && !cmd->off)
		{
			cmd->off = 1;
		}
		cmd->life = 0;
		cmd->on = 0;
		cmd = cmd->next;
	}
}

void	vm_rev_pc(t_vm *vm, t_cmd *cmd)
{
	int		id;

	id = -1;
	while (cmd)
	{
		if (!cmd->on)
		{
			id = cmd->pl * -1;
			if (id > -1 && vm->tab_champ[id].nbr_process > 0)
				vm->tab_champ[id].nbr_process -= 1;
		}
		cmd = cmd->next;
	}
}


void	vm_cycler_todie(t_vm *vm, int *i)
{
	vm_rev_pc(vm, vm->cmd);
	vm_curet_next(vm->cmd);
	if (vm->lifes == 0 || (vm->cycle_to_die) < 0)
	{
		*i = 0;
		vm->cycle_to_die = 0;
	}
	vm->last_check++;
	if (vm->last_check == MAX_CHECKS || vm->lifes >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->cycle_to_die < 0)
			vm->cycle_to_die = 0;
		vm->last_check = 0;
	}
	pl_period_live(vm);
	vm->cycle = 0;
	vm->lifes = 0;
}

/*void	vm_cycler_to_die(t_vm *vm, int *i)
{
	if (vm->cycle >= vm->cycle_to_die)
	{
		vm_cycler_todie(vm, i);
	}
	else
	{
		vm->cycle++;
		vm->total_cycle++;
	}
}*/

void	vm_cycler_to_die(t_vm *vm, int *i)
{
	// int		yes;
	// t_cmd	*cmd;

	// yes = 0;
	// cmd = vm->cmd;
	if (vm->cycle >= vm->cycle_to_die)
	{
		vm_cycler_todie(vm, i);
	}
	// else
	// {
	// 	while (cmd)
	// 	{
	// 		if (cmd->lnew)
	// 			yes = 1;
	// 		//cmd->lnew = 0;
	// 		cmd = cmd->next;
	// 	}
	// 	if (!yes)
	// 	{
	// 		vm->cycle++;
	// 		vm->total_cycle++;
	// 	}
	// }
}

void	vm_count(t_vm *vm, t_cmd *cmd)
{
	 int		yes;

	 yes = 0;
	 	while (cmd)
	 	{
	 		if (cmd->lnew)
	 			yes = 1;
	 		cmd = cmd->next;
	 	}
	 	if (!yes)
	 	{
			vm->cycle++;
			vm->total_cycle++;
		}
}

int		vm_cout(t_cmd *cmd)
{
	 int		yes;

	 yes = 0;
	 	while (cmd)
	 	{
	 		if (cmd->lnew)
	 			yes++;
	 		cmd = cmd->next;
	 	}
	 return (yes);
}

void	vm_set_cycle_wait(t_vm *vm, t_cmd *cmd)
{
	int		acb;

	acb = vm->arena[mdx(cmd->idx)].acb - 1;
	if (vm_its_cmd2(vm, cmd))
	{
		vm->arena[cmd->idx].hit = 1;
		vm->arena[cmd->idx].pl = cmd->pl;

		// if (cmd->lnew)
		// {
		// 	cmd->wait = op_tab[acb].cycles;// - (vm->total_cycle - cmd->str_cycle);
		// }
		// else
			cmd->wait = op_tab[acb].cycles + (cmd->wait == -1 ? cmd->wait * - 1 : 0);
		/*if (vm->total_cycle == 0)
			cmd->str_cycle = vm->total_cycle;
		if (cmd->lnew)
		{
			cmd->str_cycle = vm->total_cycle - 1;
		}
		else
			cmd->str_cycle = cmd->str_cycle;*/

		//cmd->wait = op_tab[acb].cycles - 2;
		//cmd->lnew = 0;
		cmd->playing = 1;
	}
	else
		vm_next_step(vm, cmd, 1);
}

/*void	vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		pos;
	int		hex;

	hex = vm->arena[mdx(cmd->idx)].acb & 0xFF;
	pos = vm->total_cycle - cmd->str_cycle;
	//cmd->wait--;
	if (pos == cmd->wait)
	{
		if (vm_its_cmd2(vm, cmd))
		{
			cmd->str_cycle = vm->total_cycle;
			vm_cmd_triger(vm, cmd, hex);
			cmd->wait = 0;
			cmd->playing = 0;
		}
	}
	//else
	//	cmd->wait--;
}*/


void	vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		hex;

	hex = vm->arena[mdx(cmd->idx)].acb & 0xFF;
    //cmd->wait -= 1;
	if (cmd->wait == 1)
	{
		if (vm_its_cmd2(vm, cmd))
		{
			vm_cmd_triger(vm, cmd, hex);
		}
		cmd->playing = 0;
	}
	//else
	//	cmd->wait -= 1;
}



/*void	vm_list_reverse(t_cmd **cmd)
{
	t_cmd		*list;
	t_cmd		*tmp;
	t_cmd		*tmp2;

	list = *cmd;
	tmp2 = NULL;
	while (list)
	{
		tmp = list->next;
		list->next = tmp2;
		tmp2 = list;
		list = tmp;
	}
	*cmd = tmp2;
}*/

void    vm_decr(t_vm *vm, t_cmd *cmd)
{
	//if (vm->cycle > 0)
	if (cmd)
	{
	    while (cmd)
	    {
	    	if (cmd->playing)
	        	cmd->wait -= 1;
	        cmd = cmd->next;
	    }		
	}
    vm->cycle++;
    vm->total_cycle++;
}

void	vm_load_arena(t_vm *vm)
{
	int		i;
	t_cmd	*c;
	//t_cmd	*tc;

	i = 1;
	if (!vm->debug && vm->dump_cycle == -1)
	{
		vm_load_ncurses();
	}
	while (i)
	{	
		c = vm->cmd;
        vm_decr(vm, vm->cmd);
		while (c)
		{
            if (!c->off)
			{
                if (!c->playing)
				{
                    vm_set_cycle_wait(vm, c);
                }
                else
                {
                    vm_run_waiting_cycle(vm, c);
                }
            }
            if (c->next == NULL)
			{
                vm_cycler_to_die(vm, &i);
            }
            c = c->next;
        }
        //if (!vm->debug)
        vm_play_arena(vm);
        //usleep(20000);
    }
    if (!vm->debug && vm->dump_cycle == -1)
	{
        getch();
        endwin();
    }
}

static void	free_vm(t_vm *vm)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;
	int		i;

	i = -1;
	while (++i < vm->nbr_next)
	{
		free(vm->tab_champ[i].name);
		free(vm->tab_champ[i].prog);
	}
	if (vm->cmd)
	{
		tmp = vm->cmd;
		while (tmp)
		{
			tmp1 = tmp;
			tmp = tmp->next;
			free(tmp1);
		}
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
		vm->tab_champ[i].rgb = 1 + (i % 4);
		vm->tab_champ[i].id = -1;
		vm->tab_champ[i].nbr_process = 1;
		vm->tab_champ[i].alive = 0;
		vm->tab_champ[i].old_check = 0;
		vm->tab_champ[i].prev_live = 0;
		vm->tab_champ[i].lives_in_period = 0;
		i++;
	}
	vm->fd = 0;
	vm->dump_cycle = -1;
	vm->nbr_next = 0;
	vm->last_check = 0;
	vm->total_lives_period = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_before_checking = CYCLE_TO_DIE;
	vm->lifes = 0;
	vm->win = -1;
	vm->total_process = 1;
	vm->cycle = 0;
	vm->total_cycle = 0;
	vm->debug = 0;
	vm->cmd = NULL;
}

t_cmd		*add_list(t_vm *vm, int i)
{
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		lst->reg[0] = (vm->tab_champ[i].id * -1);
		lst->idx = vm->tab_champ[i].idx;//индекс первой  позиции курсора
		lst->pl = (vm->tab_champ[i].id * -1);
		lst->previdx = (vm->arena[lst->idx].acb) & 0xFF;//del?
		lst->rgb = 5 + (i % 4);//цвет каретки		
		lst->playing = 0;
		lst->wait = 0;
		lst->off = 0;
		lst->carry = 0;
		lst->life = 0;
		lst->nbr_process = 1;
		lst->flag = 0;		
		lst->on = 0;
		lst->str_cycle = 0;
		lst->lnew = 0;
		lst->next = NULL;
		lst->prev = NULL;
		//ft_printf("lst->idx |%d\n|", lst->idx);
	}	
	return (lst);
}

void	vm_glow_cur(t_vm *vm, t_cmd *cmd)
{
	//while (cmd && !cmd->flag)
	while (cmd)
	{
		//ft_printf("vm_glow_cur id player|%d|\n", cmd->reg[0]);
		vm_next_step(vm, cmd, 0);
		cmd = cmd->next;
	}
}

void	vm_load_lists(t_cmd **cmd, t_vm *vm)
{
	int		i;
	t_cmd	*tmp;

	i = -1;
	while (++i < vm->nbr_next)
	{
		tmp = *cmd;
		if (tmp)
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = add_list(vm, i);
			tmp->next->prev = *(cmd);
			//tmp->next->flag = 1;
		}
		else
			*cmd = add_list(vm, i);
		ft_printf("@@@ %d %d\n", vm->tab_champ[i].id, vm->tab_champ[i].idx);
	}
	//vm_glow_cur(vm, *cmd);
}

int			main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc < 2)
		vm_usage(argc, argv);
	vm = ft_memalloc(sizeof(t_vm));
	vm->last_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	init(vm);
	vm_create_arena(vm);
	if (vm_get_param(argv, vm, argc) == 0)
		vm_usage(argc, argv);
	vm_load_champs(vm);
	vm_load_lists(&vm->cmd, vm);
	vm_glow_cur(vm, vm->cmd);
	//нужно дописать функцию самой игры и реализовать функции
	vm_load_arena(vm);	
	//ft_printf("main vm->tab_champ[0].weight %d\n", vm->tab_champ[0].weight);
	free_vm(vm);
	return (0);
}
