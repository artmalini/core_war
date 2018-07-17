
#include "vm.h"

/*
** 144 == (T_DIR, T_REG)
** 208 == (T_IND, T_REG)
*/

void	vm_lld_dr(t_vm *vm, t_cmd *cmd, int one)
{
	cmd->reg[vm->arena[mdx(cmd->idx + 6)].acb - 1] = one;
	if (one == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
	vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
}

void	vm_lld_ir(t_vm *vm, t_cmd *cmd)
{
	short	two;
	int		pos;
	int		val;
	char	hex;

	two = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
	val = mdx(cmd->idx + two);
	pos = 0xFF & vm->arena[val].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 1].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 2].acb;
	pos <<= 8;
	pos += 0xFF & vm->arena[val + 3].acb;
	hex = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
	if (vm_v_cmd(hex - 1, hex - 1, hex - 1))
	{
		cmd->reg[vm->arena[mdx(cmd->idx + 4)].acb - 1] = pos;
		cmd->carry = (pos == 0) ? 1 : 0;
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
}

void	vm_lld(t_vm *vm, t_cmd *cmd)
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
			vm_lld_dr(vm, cmd, one);
	}
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 208)
		vm_lld_ir(vm, cmd);
}