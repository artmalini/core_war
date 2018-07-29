
#include "vm.h"

int			mdx(int nbr)
{
	int		ret;

	ret = (nbr % MEM_SIZE < 0) ? (nbr % MEM_SIZE + MEM_SIZE) : nbr % MEM_SIZE;
	return (ret);
}

int			vm_pos_curs_cdg(t_vm *vm, t_cmd *cmd, int l, int bitln)
{
	int		i;

	i = 6;
	while (i > 0)
	{
		if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== REG_CODE)
			bitln += 1;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== DIR_CODE && l == 4)
			bitln += 4;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== DIR_CODE && l == 2)
			bitln += 2;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3)
			== IND_CODE)
			bitln += 2;
		i -= 2;		
	}
	return (bitln);
}

int			vm_pos_curs(t_vm *vm, t_cmd *cmd)
{	
	int		bitln;
	int		l;

	bitln = 1;
	if (op_tab[vm->arena[cmd->idx].acb - 1].size == 0)
		l = 4;
	if (op_tab[vm->arena[cmd->idx].acb - 1].size == 1)
		l = 2;
	if (op_tab[vm->arena[cmd->idx].acb - 1].codage != 0)
		bitln += 1;
	return (vm_pos_curs_cdg(vm, cmd, l, bitln));
}

/*int		vm_pos_curs(t_vm *vm, t_cmd *cmd)
{
	int		i;
	int		bitln;
	int		l_size;

	bitln = 1;
	if (op_tab[vm->arena[cmd->idx].acb - 1].size == 0)
		l_size = 4;
	if (op_tab[vm->arena[cmd->idx].acb - 1].size == 1)
		l_size = 2;
	if (op_tab[vm->arena[cmd->idx].acb - 1].codage != 0)
		bitln += 1;
	i = 6;
	while (i > 0)
	{
		if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == REG_CODE)
			bitln += 1;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == DIR_CODE && l_size == 4)
			bitln += 4;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == DIR_CODE && l_size == 2)
			bitln += 2;
		else if (((vm->arena[cmd->idx + 1].acb >> i) & 3) == IND_CODE)
			bitln += 2;
		i -= 2;
	}
	return (bitln);
}
*/
void		vm_winner(t_vm *vm)
{
	int		i;
	int		j;

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
			ft_printf("Contestant %d, \"%s\", has won !\n",
				vm->tab_champ[j].id, vm->tab_champ[j].name);
	}
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