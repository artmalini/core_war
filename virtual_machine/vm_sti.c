
#include "vm.h"

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
	//int		tmp;
	//short	tmp;	

	i = vm_pos_curs(vm, cmd);
	//vm->arena[idx()] =
	direct = 0;
	//tmp = 0;
	/*if (((vm->arena[mdx(cmd->idx + 1)].acb >> 6) & 3) == REG_CODE)
	{
		vm->arena[mdx(cmd->idx)].rgb = cmd->rgb - 5;
		//vm->arena[cmd->idx].asc_rgb = cmd->rgb - 5;
		direct = ((cmd->idx - 1) + (0xFF & vm->arena[mdx(cmd->idx + 2)].acb));//PC + первый арг
		if (((vm->arena[mdx(cmd->idx + 1)].acb >> 4) & 3) == DIR_CODE)
		{
			tmp = (0xFF & vm->arena[mdx(cmd->idx + 3)].acb) << 8 |
							(0xFF & vm->arena[mdx(cmd->idx + 4)].acb);//второй
			direct += (0xFF & vm->arena[mdx(cmd->idx + 5)].acb << 8) |
				(0xFF & vm->arena[mdx(cmd->idx + 6)].acb);//третий
			direct += tmp;
		}
		if (((vm->arena[mdx(cmd->idx + 1)].acb >> 4) & 3) == IND_CODE)
		{
			tmp = vm->arena[mdx(cmd->idx + 3)].acb << 8 |
							vm->arena[mdx(cmd->idx + 4)].acb;
			tmp = tmp % 512;
			// direct = vm->arena[mdx(cmd->idx + tmp)].acb << 24 |
			// 			vm->arena[mdx(cmd->idx + tmp + 1)].acb << 16 |
			// 			vm->arena[mdx(cmd->idx + tmp + 2)].acb << 8 |
			// 			vm->arena[mdx(cmd->idx + tmp + 3)].acb;
			direct = 0xFF & vm->arena[mdx(cmd->idx + tmp)].acb;
			direct <<= 8;
			direct = 0xFF & vm->arena[mdx(cmd->idx + tmp + 1)].acb;
			direct <<= 8;
			direct = 0xFF & vm->arena[mdx(cmd->idx + tmp + 2)].acb;
			direct <<= 8;
			direct = 0xFF & vm->arena[mdx(cmd->idx + tmp + 3)].acb;
		}
	}*/
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 104)
	{
		vm->arena[mdx(cmd->idx)].rgb = cmd->rgb - 5;

		direct = (cmd->idx - 1) + (0xFF & vm->arena[mdx(cmd->idx + 2)].acb) + 
					((short)((0xFF & vm->arena[mdx(cmd->idx + 3)].acb) << 8 |
																	(0xFF & vm->arena[mdx(cmd->idx + 4)].acb)) + 
										(short)((0xFF & vm->arena[mdx(cmd->idx + 5)].acb << 8) |
														(0xFF & vm->arena[mdx(cmd->idx + 6)].acb)) % 512);//третий	

	}
	load_res(vm, cmd, direct);
	//ft_printf("cmd->idx |%d| direct|%d| cmd->idx|%d| ", cmd->idx, direct, cmd->reg[0]);	
	//vm->arena[direct].rgb = cmd->rgb - 5;
	//vm->arena[direct].asc_rgb = cmd->rgb - 5;
	vm_next_step(vm, cmd, i);
	//ft_printf("vm_sti cycle|%d| i |%d|\n", vm->cycle, i);
	//vm_next_step(vm, cmd, pos);	
}
