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

int			dia(int nb)
{
	if (nb >= 0 && nb <= 15)
		return (1);
	return (0);
}

int			vm_new_step(t_vm *vm, t_cmd *cmd, int run)
{
	int		chk;
	int		acb;
	int		i;
	int		len;

	len = 1;
	i = -2;
	chk = (vm->arena[mdx(cmd->idx)].acb & 0xFF) - 1;
	acb = vm->arena[mdx(cmd->idx + 1)].acb & 0xFF;
	if (dia(chk))
	{
		i = op_tab[chk].nbr_args - 1;
		if (op_tab[chk].codage)
			len++;
		while (i >= 0)
		{
			if ((acb >> (6 - i * 2) & 0x3) == REG_CODE)
				len += 1;
			else if ((acb >> (6 - i * 2) & 0x3) == DIR_CODE)
			{
				if (op_tab[chk].size)
					len += 2;
				else
					len += 4;
			}
			else if ((acb >> (6 - i * 2) & 0x3) == IND_CODE)
				len += 2;
			i--;
		}
	}
	if (i == -2 && run == 1)
		len++;
	return (len);
}

int			vm_old_step(t_vm *vm, t_cmd *cmd)
{
	int		chk;
	int		acb;
	int		i;
	int		len;

	len = 1;
	chk = (vm->arena[mdx(cmd->idx)].o_acb & 0xFF) - 1;
	acb = vm->arena[mdx(cmd->idx + 1)].acb & 0xFF;
	if (dia(chk))
	{
		i = op_tab[chk].nbr_args - 1;
		if (op_tab[chk].codage)
			len++;
		while (i >= 0)
		{
			if ((acb >> (6 - i * 2) & 0x3) == REG_CODE)
				len += 1;
			else if ((acb >> (6 - i * 2) & 0x3) == DIR_CODE)
			{
				if (op_tab[chk].size)
					len += 2;
				else
					len += 4;
			}
			else if ((acb >> (6 - i * 2) & 0x3) == IND_CODE)
				len += 2;
			i--;
		}
	}
	return (len);
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
	//int		o_hex;
	//int		cell;
	//int		id;

	//cell = 0;
	acb = vm->arena[mdx(cmd->idx)].acb - 1;
	//o_hex = (vm->arena[mdx(cmd->idx)].o_acb & 0xFF);
	if (vm_its_cmd(vm, cmd))
	{
		//if (vm->total_cycle < 2)
		//	return ;
		// if (vm->total_cycle != 4)
		// {
		// 	id = vm_getpl(vm, cmd->pl * -1);
		// 	if (id > -1 && vm->tab_champ[id].ready != 0)
		// 	{
		// 		vm->tab_champ[id].ready--;
		// 		cmd->playing = 0;
		// 			return ;
		// 	}
		// }
		if (vm->arena[mdx(cmd->idx)].overlap == 1)
		    cmd->overlap = 1;
		//vm->arena[mdx(cmd->idx)].overlap = 0;
		vm->arena[mdx(cmd->idx)].o_acb = acb + 1;
		vm->arena[mdx(cmd->idx)].o_hex = vm->arena[mdx(cmd->idx + 1)].acb;
		vm->arena[mdx(cmd->idx)].hit = cmd->idx;
		vm->arena[mdx(cmd->idx)].pl = cmd->pl;
		cmd->wait = op_tab[acb].cycles;// + cell + (cmd->wait == -1 ? cmd->wait * -1 : 0);
		cmd->playing = 1;
		cmd->lnew = 0;
	}
	else
	{
		//if (acb == -1 && o_hex != 0)
		if (acb >= 0 && acb < 16)
		{
			if (vm->arena[mdx(cmd->idx)].zero == 0)
				cmd->zero = 1;				
			cmd->wait = op_tab[acb].cycles;
			cmd->playing = 1;
			cmd->lnew = 1;
			vm->arena[mdx(cmd->idx)].overlap = 0;
		}
		else
			vm_next_step(vm, cmd, 1);
	}
}

void		vm_store_args(t_vm *vm, t_cmd *cmd, int *c_tmp)
{
	int		i;

	i = -1;
	while (++i < 7)
		c_tmp[i] = 0;
	i = -1;
	while (++i < 7)
		c_tmp[i] = vm->arena[mdx(cmd->idx + i)].acb;
}

void		vm_old_args(t_vm *vm, t_cmd *cmd, int *tmp)
{
	int		i;

	i = -1;
	while (++i < 7)
		tmp[i] = 0;
	i = -1;
	while (++i < 7)
	{
		if (vm->arena[mdx(cmd->idx + i)].overlap == 1)
			tmp[i] = vm->arena[mdx(cmd->idx + i)].o_args;
	}
	i = -1;
	while (++i < 7)
	{
		if (tmp[i] != 0)
			vm->arena[mdx(cmd->idx + i)].acb = tmp[i];
	}
}

void		vm_put_cur_arg(t_vm *vm, t_cmd *cmd, int *c_tmp, int *tmp)
{
	int		i;

	i = -1;
	while (++i < 7)
	{
		if (tmp[i] != 0 && vm->arena[mdx(cmd->idx + i)].o_acb == c_tmp[i])
			vm->arena[mdx(cmd->idx + i)].acb = c_tmp[i];
	}
}


void		vm_run_waiting_cycle(t_vm *vm, t_cmd *cmd)
{
	int		hex;
	int		o_hex;
	int		hit;
	int		prev;
	int		run;
    int     zero;
   // int		c_tmp[7];
   // int		tmp[7];

	hex = vm->arena[mdx(cmd->idx)].acb & 0xFF;
	o_hex = (vm->arena[mdx(cmd->idx)].o_acb & 0xFF);
    zero = vm->arena[mdx(cmd->idx)].zero & 0xFF;
   // (void)zero;
	//hit = (vm->arena[mdx(cmd->idx)].hit);
	prev = 0;
	run = 0;
	if (cmd->wait == 1)
	{
		if (hex != o_hex && !cmd->lnew)
		{
			hit = (vm_its_cmd_old(vm, cmd)) + 1;
			if (hit == o_hex && !cmd->zero)
			{
				vm_cmd_triger(vm, cmd, hit);
				prev = 1;
			}
			else if (hit == -1 && hex == 255 && dia(o_hex - 1))
				vm_next_step(vm, cmd, vm_old_step(vm, cmd));
			else if (hit == -1 && hex == 0 && o_hex != 0)
				vm_next_step(vm, cmd, 2);
			else
				vm_cmd_triger(vm, cmd, hex);
		}
		else if ((hex == o_hex) && vm->arena[mdx(cmd->idx)].overlap == 1 && cmd->overlap == 0 && !cmd->lnew)
		{
			vm_cmd_triger(vm, cmd, cmd->previdx + 1);
			//if (vm->arena[mdx(cmd->idx)].hit == 1)
				//vm->arena[mdx(cmd->idx)].overlap = 0;
		}
		else if (vm_its_cmd(vm, cmd) && !prev && !cmd->lnew)
		{
			//needed for old args
			//vm_store_args(vm, cmd, c_tmp);
			//vm_old_args(vm, cmd, tmp);
			vm_cmd_triger(vm, cmd, hex);
			//vm_put_cur_arg(vm, cmd, c_tmp, tmp);
		}
		else if (cmd->lnew)
		{			
			cmd->lnew = 0;
			if (o_hex == 0 && hex != 0 && (cmd->zero == 1 && zero == 1))
				run = 1;
			cmd->zero = 0;
			vm_next_step(vm, cmd, vm_new_step(vm, cmd, run));
		}
		//cmd->overlap = 0;
		//if (vm->arena[mdx(cmd->idx)].hit != 0)
		//	vm->arena[mdx(cmd->idx)].hit = 0;
		//vm->arena[mdx(cmd->idx)].zero = 0;
		//vm->arena[mdx(cmd->idx)].overlap = 0;
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
			if (*nb == 150000)
				*nb = 150;
			else
				*nb = 150000;
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

	nb = 150000;
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
