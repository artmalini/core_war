
#include "vm.h"
int		mdx(int nbr)
{
	int		ret;

	ret = (nbr % MEM_SIZE < 0) ? (nbr % MEM_SIZE + MEM_SIZE) : nbr % MEM_SIZE;
	return (ret);
}

int		vm_read(t_vm *vm, t_cmd *cmd)
{
	int		i;
	int		bitln;

	i = 6;
	bitln = 1;
	if (op_tab[vm->arena[cmd->idx].acb - 1].codage != 0)
		bitln += 1;
	while (i > 0)
	{
		if (((vm->arena[cmd->idx + 1].acb >> i) & 3 ) == REG_CODE)
			bitln += 1;
		else
			bitln += 2;
		i -= 2;
	}

	//bitln = (vm->arena[cmd->idx + 1].acb >> 6) & 3;

	return (bitln);
}

/*int		sti_cells(t_vm *vm, t_cmd *cmd)
{
	char	low;
	short	med;
	int		big;

	if (((vm->arena[cmd->idx + 1].acb >> 6) & 3) == REG_CODE)
	{
		
		//vm->arena[cmd->idx].asc_rgb = cmd->rgb - 5;
		//low = (cmd->idx - 1) + vm->arena[cmd->idx + 2].acb;//PC + первый арг		
		low = vm->arena[cmd->idx + 2].acb;//PC + первый арг
		if (((vm->arena[cmd->idx + 1].acb >> 4) & 3) == DIR_CODE)
		{
			med = vm->arena[cmd->idx + 4].acb << 8 |
				vm->arena[cmd->idx + 5].acb;//третий
		}
		if (((vm->arena[cmd->idx + 1].acb >> 4) & 3) == IND_CODE)
		{
			med = vm->arena[cmd->idx + 3].acb << 8 |
				vm->arena[cmd->idx + 4].acb;
			big = (int)(mdx(vm->arena[cmd->idx].acb) << 24 |
						mdx(vm->arena[cmd->idx + 1].acb) << 16 |
						mdx(vm->arena[cmd->idx + 2].acb) << 8 |
						mdx(vm->arena[cmd->idx + 3].acb));
			//low += vm->arena[cmd->idx + 7].acb << 8 |
			return ((low + med + big) % 512);
		}
	}
	return ((low + med) % 512);
}*/

void	load_res(t_vm *vm, t_cmd *cmd, int direct)
{
	int		i;

	i = -1;
	while (++i <= 3)
	{
		vm->arena[mdx(direct + i)].acb = (cmd->reg[0] >> ((3 - i) * 8)) & 0xFF;
		//ft_printf("cmdREG|%d|\n", (cmd->reg[0] >> ((3 - i) * 8)) & 0xFF);
	}
}

void	vm_sti(t_vm *vm, t_cmd *cmd)
{
	int		i;
	int		direct;
	int		tmp;	

	i = vm_read(vm, cmd);
	//vm->arena[idx()] =
	direct = 0;
	tmp = 0;
	if (((vm->arena[mdx(cmd->idx + 1)].acb >> 6) & 3) == REG_CODE)
	{
		vm->arena[mdx(cmd->idx)].rgb = cmd->rgb - 5;
		//vm->arena[cmd->idx].asc_rgb = cmd->rgb - 5;
		direct = (cmd->idx - 1) + vm->arena[mdx(cmd->idx + 2)].acb;//PC + первый арг
		if (((vm->arena[mdx(cmd->idx + 1)].acb >> 4) & 3) == DIR_CODE)
		{
			tmp = vm->arena[mdx(cmd->idx + 3)].acb << 8 |
							vm->arena[mdx(cmd->idx + 4)].acb;//второй
			direct += vm->arena[mdx(cmd->idx + 5)].acb << 8 |
				vm->arena[mdx(cmd->idx + 6)].acb;//третий
			direct += tmp;
		}
		if (((vm->arena[mdx(cmd->idx + 1)].acb >> 4) & 3) == IND_CODE)
		{
			tmp = vm->arena[mdx(cmd->idx + 3)].acb << 8 |
							vm->arena[mdx(cmd->idx + 4)].acb;
			tmp = tmp % 512;
			direct = vm->arena[mdx(cmd->idx + tmp)].acb << 24 |
						vm->arena[mdx(cmd->idx + tmp + 1)].acb << 16 |
						vm->arena[mdx(cmd->idx + tmp + 2)].acb << 8 |
						vm->arena[mdx(cmd->idx + tmp + 3)].acb;
			//direct += vm->arena[cmd->idx + 7].acb << 8 |
			//	vm->arena[cmd->idx + 8].acb;//третий
		}
	}
	load_res(vm, cmd, direct);
	//ft_printf("cmd->idx |%d| tmp|%d| direct|%d| cmd->idx|%d|\n", cmd->idx, tmp, direct, cmd->reg[0]);	
	//vm->arena[direct].rgb = cmd->rgb - 5;
	//vm->arena[direct].asc_rgb = cmd->rgb - 5;
	vm_next_step(vm, cmd, i);
	//printf("vm_sti cycle|%d| i |%d|\n", vm->cycle, i);
	//vm_next_step(vm, cmd, pos);	
}
