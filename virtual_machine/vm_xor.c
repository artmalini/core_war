
#include "vm.h"

/*
** 100 == (T_REG, T_DIR, T_REG)
** 84  == (T_REG, T_REG, T_REG)
** 116 == (T_REG, T_IND, T_REG)
** 148 == (T_DIR, T_REG, T_REG)
** 180 == (T_DIR, T_IND, T_REG)
** 164 == (T_DIR, T_DIR, T_REG)
** 212 == (T_IND, T_REG, T_REG)
** 228 == (T_IND, T_DIR, T_REG)
** 244 == (T_IND, T_IND, T_REG)
*/

void	vm_xor_5(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 212)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
		arg[2] = 0;
		arg[3] = 0;
		arg[4] = 0;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_irr(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
}

void	vm_xor_4(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 148)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 7)].acb;
		arg[2] = 0;
		arg[3] = 2;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[1] - 1))
			vm_drr(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	else if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 116)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
		arg[2] = 0;
		arg[3] = 0;
		arg[4] = 0;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[1] - 1))
			vm_rir(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	vm_xor_5(vm, cmd, arg);
}

void	vm_xor_3(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 180)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 8)].acb;
		arg[1] = 0;
		arg[2] = 0;
		arg[3] = 2;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_dir_bit(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	else if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 164)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 10)].acb;
		arg[1] = 0;
		arg[2] = 0;
		arg[3] = 2;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_ddr(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	vm_xor_4(vm, cmd, arg);
}

void	vm_xor_2(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 228)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 8)].acb;
		arg[1] = 0;
		arg[2] = 0;
		arg[3] = 4;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_idr_bit(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	else if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 244)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
		arg[1] = 0;
		arg[2] = 0;
		arg[3] = 0;
		arg[4] = 0;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_iir_bit(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	else
		vm_xor_3(vm, cmd, arg);
}

void	vm_xor(t_vm *vm, t_cmd *cmd)
{
	int	arg[5];

	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 100)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 7)].acb;
		arg[2] = 0;
		arg[3] = 3;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[1] - 1))
			vm_rdr_bit(vm, cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	else if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 84)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
		arg[2] = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		if (vm_v_cmd(arg[0] - 1, arg[1] - 1, arg[2] - 1))
			vm_rrr_bit(cmd, arg, 3);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));		
	}
	else
		vm_xor_2(vm, cmd, arg);
}