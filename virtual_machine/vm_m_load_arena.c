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

int			vm_check_big(t_vm *vm, t_cmd *cmd, int chk)
{
	int		i;
	int		acb;
	int		arg;

	arg = op_tab[chk].nbr_args;
	acb = vm->arena[mdx(cmd->idx + 1)].acb & 0xFF;
	i = -1;
	while (++i < arg)
	{
		if ((acb >> (6 - i * 2) & 0x3) == REG_CODE &&
				(op_tab[chk].type_params[i] & T_REG) == T_REG)
			;
		else if ((acb >> (6 - i * 2) & 0x3) == DIR_CODE &&
				(op_tab[chk].type_params[i] & T_DIR) == T_DIR)
			;
		else if ((acb >> (6 - i * 2) & 0x3) == IND_CODE &&
				(op_tab[chk].type_params[i] & T_IND) == T_IND)
			;
		else
			return (0);
	}
	return (1);
}

int			vm_its_cmd(t_vm *vm, t_cmd *cmd)
{
	int		chk;

	chk = (vm->arena[mdx(cmd->idx)].acb & 0xFF) - 1;
	if (chk < 0 || chk > 16)
		return (0);
	if (chk == 0 || chk == 8 || chk == 11 || chk == 14)
		return (1);
	else if (vm_check_big(vm, cmd, chk))
		return (1);
	else
		return (0);
}

int			vm_its_cmd_old(t_vm *vm, t_cmd *cmd)
{
	int		chk;

	chk = (vm->arena[mdx(cmd->idx)].o_acb & 0xFF) - 1;
	if (chk < 0 || chk > 16)
		return (-2);
	if (chk == 0 || chk == 8 || chk == 11 || chk == 14)
		return (chk);
	else if (vm_check_big(vm, cmd, chk))
		return (chk);
	else
		return (-2);
}

void		vm_set_cycle_wait(t_vm *vm, t_cmd *cmd)
{
	int		acb;
	int		cell;
	int		id;

	cell = 0;
	acb = vm->arena[mdx(cmd->idx)].acb - 1;
	if (vm_its_cmd(vm, cmd))
	{
		if (vm->total_cycle != 4)
		{
			id = vm_getpl(vm, cmd->pl * -1);
			if (id > -1 && vm->tab_champ[id].ready != 0)
			{
				vm->tab_champ[id].ready--;
				cmd->playing = 0;
					return ;
			}
		}
		vm->arena[mdx(cmd->idx)].o_acb = acb + 1;
		//vm->arena[mdx(cmd->idx)].hit = cmd->idx;
		vm->arena[mdx(cmd->idx)].pl = cmd->pl;
		cmd->wait = op_tab[acb].cycles + cell;// + (cmd->wait == -1 ? cmd->wait * -1 : 0);		
		cmd->playing = 1;
	}
	else
		vm_next_step(vm, cmd, 1);
}

void		vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		hex;
	int		o_hex;
	int		hit;
	int		prev;

	hex = vm->arena[mdx(cmd->idx)].acb & 0xFF;
	o_hex = (vm->arena[mdx(cmd->idx)].o_acb & 0xFF);
	//hit = (vm->arena[mdx(cmd->idx)].hit);
	prev = 0;
	if (cmd->wait == 1)
	{
		if (hex != o_hex)
		{
			hit = (vm_its_cmd_old(vm, cmd)) + 1;
			if (hit == o_hex)
			{
				vm_cmd_triger(vm, cmd, hit);
				prev = 1;
			}
			else
				vm_cmd_triger(vm, cmd, hex);
		}
		else if (vm_its_cmd(vm, cmd) && !prev)
			vm_cmd_triger(vm, cmd, hex);
		cmd->playing = 0;
	}
}

void		vm_decr(t_vm *vm, t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->playing)
			cmd->wait -= 1;
		cmd = cmd->next;
	}
	vm->cycle++;
	vm->total_cycle++;
}

void		vm_sleep(t_vm *vm, int *pause, int *nb)
{
	int entry;

	if (vm->visual)
	{
		
		entry = 0;
		nodelay(stdscr, 1);
		entry = getch();
		if (entry == 32)
		{
			if (*nb == 50000)
				*nb /= 1000;
			else
				*nb = 50000;
		}
		if (entry == 'z')
		{
			if (*pause == 1)
				*pause = 0;
			else
				*pause = 1;
		}
		nodelay(stdscr, 0);
		usleep(*nb);
	}
}

void		vm_load_arena(t_vm *vm)
{
	int		i;
	t_cmd	*c;
	int		pause;
	int		nb;

	nb = 50000;
	i = 1;
	pause = 1;
	while (i)
	{
		vm_sleep(vm, &pause, &nb);
		if (pause)
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
		}
	}
}
