/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_m_load_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:17:31 by amakhiny          #+#    #+#             */
/*   Updated: 2018/07/30 12:17:34 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_play_arena(t_vm *vm)
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

int			vm_its_cmd(t_vm *vm, t_cmd *cmd)
{
	int		i;

	i = (vm->arena[mdx(cmd->idx)].acb & 0xFF) - 1;
	if (i < 0 || i > 16)
		return (0);
	else
		return (1);
}

void		vm_set_cycle_wait(t_vm *vm, t_cmd *cmd)
{
	int		acb;

	acb = vm->arena[mdx(cmd->idx)].acb - 1;
	if (vm_its_cmd(vm, cmd))
	{
		vm->arena[cmd->idx].hit = 1;
		vm->arena[cmd->idx].pl = cmd->pl;
		cmd->wait = op_tab[acb].cycles + (cmd->wait == -1 ? cmd->wait * -1 : 0);
		cmd->playing = 1;
	}
	else
	{
		// if (vm->arena[mdx(cmd->idx + 1)].acb == 0)
		// {
		// 	cmd->rgb = 11;
		// }
		vm_next_step(vm, cmd, 1);
	}
}

void		vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		hex;

	hex = vm->arena[mdx(cmd->idx)].acb & 0xFF;
	if (cmd->wait == 1)
	{
		if (vm_its_cmd(vm, cmd))
		{
			vm_cmd_triger(vm, cmd, hex);
		}
		cmd->playing = 0;
	}
}

void    	vm_decr(t_vm *vm, t_cmd *cmd)
{
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

void		vm_sleep(t_vm *vm)
{
	int		nb;
	int		ch;

	nb = 20000;
	//ch = getch();
	ch = 0;
	if (vm->visual)
	{
		while ((ch = getch()) != ERR)
		{
			if (ch == KEY_DOWN)
				nb *= 10;
		}
		usleep(nb);
		//else
		//	usleep(nb);
	}
}

void		vm_load_arena(t_vm *vm)
{
	int		i;
	t_cmd	*c;
	//int		j;
	//t_cmd	*tc;

	i = 1;
	//j = 0;
	while (i)
	{
		c = vm->cmd;
		vm_decr(vm, vm->cmd);
		while (c)
		{
            if (!c->off)
			{
                if (!c->playing) {
                    vm_set_cycle_wait(vm, c);
                }
				else {
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
		//vm_sleep(vm);
		//usleep(10000);
	}
}