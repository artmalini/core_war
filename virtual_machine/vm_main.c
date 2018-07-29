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
			if (i + 1 < MEM_SIZE)
			{
				ft_printf("\n");
				ft_printf("%#06x : ", mem);
			}
			mem += 64;
		}
		i++;
	}
	ft_printf("\n");
}





void	vm_winner(t_vm *vm)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	if (vm->win)
	{
		while (++i < vm->nbr_next)
		{
			if (vm->tab_champ[i].prev_live > vm->tab_champ[j].prev_live)
				j = i;
		}
		if (!vm->visual)
			ft_printf("Contestant %d, \"%s\", has won !\n", vm->tab_champ[j].id, vm->tab_champ[j].name);
	}
}


// void	draw_dead_pl(int j)
// {
// ##  ### ##  
// # #  #  # # 
// ##   #  ##  
// # #  #  #   
// # # ### #
// }






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

void	pl_period_live(t_vm *vm)
{
	int i;

	i = -1;
	while (++i < vm->nbr_next)
		vm->tab_champ[i].lives_in_period = 0;
}

int		vm_its_cmd(t_vm *vm, t_cmd *cmd)
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


void	vm_cycler_reset(t_vm *vm, int *i)
{
	vm_rev_pc(vm, vm->cmd);
	vm_curet_next(vm->cmd);
	if (vm->lifes == 0 || (vm->cycle_to_die) < 0)
	{
		*i = 0;
		if (vm->total_cycle > 0)
			vm->win = 1;
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
		vm_cycler_reset(vm, i);
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
		vm_cycler_reset(vm, i);
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

/*void	vm_count(t_vm *vm, t_cmd *cmd)
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
}*/

void	vm_set_cycle_wait(t_vm *vm, t_cmd *cmd)
{
	int		acb;

	acb = vm->arena[mdx(cmd->idx)].acb - 1;
	if (vm_its_cmd(vm, cmd))
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
		if (vm_its_cmd(vm, cmd))
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

void	vm_play_arena(t_vm *vm)
{
	if (vm->dump_cycle > -1)
	{
		if (vm->total_cycle == vm->dump_cycle)
			vm_dump_arena(vm);
	}
	else if (vm->visual)
	{
		vm_vis_arena(vm);
	}	
}

void	vm_load_arena(t_vm *vm)
{
	int		i;
	t_cmd	*c;
	//t_cmd	*tc;

	i = 1;
	if (vm->visual && vm->dump_cycle == -1)
		vm_load_ncurses();
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
        vm_play_arena(vm);
        if (vm->dump_cycle > -1 && (vm->dump_cycle == vm->total_cycle))
        	i = 0;
        //usleep(20000);
    }
    if (vm->visual && vm->dump_cycle == -1)
	{
        getch();
        endwin();
    }
}

int			main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc < 2)
		vm_usage(argc, argv);
	vm = ft_memalloc(sizeof(t_vm));
	vm->last_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm_init(vm);
	vm_create_arena(vm);
	if (vm_get_param(argv, vm, argc) == 0)
		vm_exit(vm);
	vm_load_champs(vm);
	vm_load_lists(&vm->cmd, vm);
	vm_glow_cur(vm, vm->cmd);
	//нужно дописать функцию самой игры и реализовать функции
	vm_load_arena(vm);
	vm_winner(vm);
	//ft_printf("main vm->tab_champ[0].weight %d\n", vm->tab_champ[0].weight);
	free_vm(vm);
	return (0);
}
