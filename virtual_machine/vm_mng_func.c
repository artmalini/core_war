
#include "vm.h"

int		mdx(int nbr)
{
	int		ret;

	ret = (nbr % MEM_SIZE < 0) ? (nbr % MEM_SIZE + MEM_SIZE) : nbr % MEM_SIZE;
	return (ret);
}

int		vm_pos_curs(t_vm *vm, t_cmd *cmd)
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
		else
			bitln += 2;
		i -= 2;
	}
	return (bitln);
}