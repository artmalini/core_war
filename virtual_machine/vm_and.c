
#include "vm.h"

void	vm_rdr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_direct(vm, cmd, arg);
	if (let == 2)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_direct(vm, cmd, arg);
	if (let == 3)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_direct(vm, cmd, arg);
	if (cmd->reg[arg[1] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_rrr(t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] & cmd->reg[arg[1] - 1];
	if (let == 2)
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] | cmd->reg[arg[1] - 1];
	if (let == 3)
		cmd->reg[arg[2] - 1] = cmd->reg[arg[0] - 1] ^ cmd->reg[arg[1] - 1];
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_idr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) & vm_direct(vm, cmd, arg);
	if (let == 2)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) | vm_direct(vm, cmd, arg);
	if (let == 3)
		cmd->reg[arg[0] - 1] = vm_indir(vm, cmd, 2) ^ vm_direct(vm, cmd, arg);
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_iir(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_indir(vm, cmd, 2);
	if (let == 2)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_indir(vm, cmd, 2);
	if (let == 3)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_indir(vm, cmd, 2);
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_dir(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) & vm_indir(vm, cmd, 6);
	if (let == 2)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) | vm_indir(vm, cmd, 6);
	if (let == 3)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) ^ vm_indir(vm, cmd, 6);
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_ddr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	int		tmp[4];

	tmp[3] = 6;
	tmp[4] = 4;
	if (let == 1)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) & vm_direct(vm, cmd, tmp);
	if (let == 2)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) | vm_direct(vm, cmd, tmp);
	if (let == 3)
		cmd->reg[arg[0] - 1] = vm_direct(vm, cmd, arg) ^ vm_direct(vm, cmd, tmp);
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_drr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_direct(vm, cmd, arg);
	if (let == 2)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_direct(vm, cmd, arg);
	if (let == 3)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_direct(vm, cmd, arg);
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_rir(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] & vm_indir(vm, cmd, 3);
	if (let == 2)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] | vm_indir(vm, cmd, 3);
	if (let == 3)
		cmd->reg[arg[1] - 1] = cmd->reg[arg[0] - 1] ^ vm_indir(vm, cmd, 3);
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}

void	vm_irr(t_vm *vm, t_cmd *cmd, int *arg, int let)
{
	if (let == 1)
		cmd->reg[arg[0] - 1] = cmd->reg[arg[0] - 1] & vm_indir(vm, cmd, 2);
	if (let == 2)
		cmd->reg[arg[0] - 1] = cmd->reg[arg[0] - 1] | vm_indir(vm, cmd, 2);
	if (let == 3)
		cmd->reg[arg[0] - 1] = cmd->reg[arg[0] - 1] ^ vm_indir(vm, cmd, 2);
	if (cmd->reg[arg[2] - 1] == 0)
		cmd->carry = 1;
	else
		cmd->carry = 0;
}



void	vm_and_5(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 212)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 5)].acb;
		arg[2] = 0;
		arg[3] = 0;
		arg[4] = 0;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_irr(vm, cmd, arg, 1);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
}

void	vm_and_4(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 148)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 6)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 7)].acb;
		arg[2] = 0;
		arg[3] = 2;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[1] - 1))
			vm_drr(vm, cmd, arg, 1);
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
			vm_rir(vm, cmd, arg, 1);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	vm_and_5(vm, cmd, arg);
}

void	vm_and_3(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 180)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 8)].acb;
		arg[1] = 0;
		arg[2] = 0;
		arg[3] = 2;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_dir(vm, cmd, arg, 1);
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
			vm_ddr(vm, cmd, arg, 1);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	vm_and_4(vm, cmd, arg);
}

void	vm_and_2(t_vm *vm, t_cmd *cmd, int *arg)
{
	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 228)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 8)].acb;
		arg[1] = 0;
		arg[2] = 0;
		arg[3] = 4;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[0] - 1))
			vm_idr(vm, cmd, arg, 1);
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
			vm_iir(vm, cmd, arg, 1);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	else
		vm_and_3(vm, cmd, arg);
}

void	vm_and(t_vm *vm, t_cmd *cmd)
{
	int	arg[4];

	if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 100)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 7)].acb;
		arg[2] = 0;
		arg[3] = 3;
		arg[4] = 4;
		if (vm_v_cmd(arg[0] - 1, arg[0] - 1, arg[1] - 1))
			vm_rdr(vm, cmd, arg, 1);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));
	}
	else if (((0xFF & vm->arena[mdx(cmd->idx + 1)].acb)) == 84)
	{
		arg[0] = 0xFF & vm->arena[mdx(cmd->idx + 2)].acb;
		arg[1] = 0xFF & vm->arena[mdx(cmd->idx + 3)].acb;
		arg[2] = 0xFF & vm->arena[mdx(cmd->idx + 4)].acb;
		if (vm_v_cmd(arg[0] - 1, arg[1] - 1, arg[2] - 1))
			vm_rrr(cmd, arg, 1);
		vm_next_step(vm, cmd, vm_pos_curs(vm, cmd));		
	}
	else
		vm_and_2(vm, cmd, arg);
}
