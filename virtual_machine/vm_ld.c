
#include "vm.h"

/*
** 144 == (T_DIR, T_REG)
** 208 == (T_IND, T_REG)
*/

void	vm_ld_dr(t_vm *vm, t_cmd *cmd, int one, int hex)
{
	if (vm->debug)
		ft_printf("|P\t%d| ld |%d| |r%d|\n", cmd->nbr_process, one, hex);
	cmd->reg[hex - 1] = one;
	if (one == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
	//ft_printf("pos |%d|", vm_pos_curs(vm, cmd));
	vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
}

void	vm_ld_ir(t_vm *vm, t_cmd *cmd)
{
	short	two;
	int		two_val;
	int		pos;
	int		val;
	int		hex;

	two = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	two_val = two % IDX_MOD;
	val = mdx(cmd->idx + two_val);
	pos = 0xFF & vm->arena[val].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 1].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 2].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 3].acb;
	hex = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm->debug)
		ft_printf("|P\t%d| ld |%d| |r%d|\n", cmd->nbr_process, pos, hex);
	if (vm_v_cmd(hex - 1, hex - 1, hex - 1))
	{
		cmd->reg[hex - 1] = pos;
		cmd->carry = (pos == 0) ? 1 : 0;
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
}

void	vm_ld(t_vm *vm, t_cmd *cmd)
{
	int		hex;
	int		one;

	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 144)
	{
		one = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		one <<= 8;
		one += 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
		hex = 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
		if (vm_v_cmd(hex - 1, hex - 1, hex - 1))
			vm_ld_dr(vm, cmd, one, hex);
	}
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 208)
		vm_ld_ir(vm, cmd);
}
