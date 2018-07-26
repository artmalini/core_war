/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:41:21 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/18 16:41:22 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*static void	load_champ_to(t_vm *vm, t_champ champ, int memory_index)
{
	int	index;

	index = 0;
	while (index < champ.weight && (index + memory_index) < MEM_SIZE)
	{
		vm->arena[index + memory_index] = (unsigned char)champ.prog[index];
		index++;
	}
}*/

void			load_res(t_vm *vm, t_cmd *cmd, int direct)
{
	int			i;
	int			reg1;
	int			dat;

	i = -1;
	reg1 =  0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	if (reg1 < 0 && reg1 >= REG_NUMBER)
		return ;
	dat = cmd->reg[reg1 - 1];
	while (++i <= 3)
	{
		vm->arena[mdx(cmd->idx + direct + i)].acb = ((dat) >> ((3 - i) * 8)) & 0xFF;
		vm->arena[mdx(cmd->idx + direct + i)].rgb = cmd->rgb - 4;
		vm->arena[mdx(cmd->idx + direct + i)].asc_rgb = cmd->rgb - 4;
		//vm->arena[mdx(direct + i)].acb = ((cmd->reg[0] * -1) >> ((3 - i) * 8)) & 0xFF;
	}
	if (vm->debug)
		ft_printf("|P\t%d| sti |%d| |r%d| val|%d| %d\n", cmd->nbr_process, direct, reg1, dat, mdx(cmd->idx + direct));
	//ft_printf("sti |%d| value|%d| jump|%d|\n", direct, dat, vm_pos_curs(vm, cmd));
}

static void		load_champ_to(t_vm *vm, int memory_index)
{
	size_t		index;

	index = 0;
	while (index < WEIGHT(PLAYER) && (index + memory_index) < MEM_SIZE)
	{
		vm->arena[index + memory_index].acb = (char)(0xFF & PROG(PLAYER)[index]);
		vm->arena[index + memory_index].rgb = 1 + (int)PLAYER % 4;
		vm->arena[index + memory_index].asc_rgb = 1 + (int)PLAYER % 4;
		index++;
	}
}

void			vm_load_champs(t_vm *vm)
{
	int			space;
	size_t		space_bt_champs;

	space = 0;
	vm->current_player = 1;
	space_bt_champs = MEM_SIZE / TOTAL_PLAYERS;
	if (TOTAL_PLAYERS == 1)
		space_bt_champs = 0;
	while (PLAYER < TOTAL_PLAYERS)
	{
		IDX(PLAYER) = space;
		//vm->tab_champ[num_pl].life = 0;
		if (vm->debug == ON)
			ft_printf("* Player %d, Start position %d\n",
					  (PLAYER + 1), IDX(PLAYER));
		load_champ_to(vm, space);
		space += space_bt_champs;
		vm->current_player++;
	}
	vm->current_player = OFF;
}
