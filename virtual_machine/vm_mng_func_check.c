
#include "vm.h"

int			vm_check_big(t_vm *vm, t_cmd *cmd, int chk)
{
	int		i;
	int		acb;
	int		arg;

	arg = g_op_tab[chk].nbr_args;
	acb = vm->arena[mdx(cmd->idx + 1)].acb & 0xFF;
	i = -1;
	while (++i < arg)
	{
		if ((acb >> (6 - i * 2) & 0x3) == REG_CODE &&
				(g_op_tab[chk].type_params[i] & T_REG) == T_REG)
			;
		else if ((acb >> (6 - i * 2) & 0x3) == DIR_CODE &&
				(g_op_tab[chk].type_params[i] & T_DIR) == T_DIR)
			;
		else if ((acb >> (6 - i * 2) & 0x3) == IND_CODE &&
				(g_op_tab[chk].type_params[i] & T_IND) == T_IND)
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


int			vm_big(t_vm *vm, t_cmd *cmd, int chk)
{
	int		i;
	int		acb;
	int		arg;

	arg = g_op_tab[chk].nbr_args;
	acb = vm->arena[mdx(cmd->idx + 1)].acb & 0xFF;
	i = -1;
	while (++i < arg)
	{
		if ((acb >> (6 - i * 2) & 0x3) == REG_CODE &&
				(g_op_tab[chk].type_params[i] & T_REG) == T_REG)
			;
		else if ((acb >> (6 - i * 2) & 0x3) == DIR_CODE &&
				(g_op_tab[chk].type_params[i] & T_DIR) == T_DIR)
			;
		else if ((acb >> (6 - i * 2) & 0x3) == IND_CODE &&
				(g_op_tab[chk].type_params[i] & T_IND) == T_IND)
			;
		else
			return (0);
	}
	return (1);
}

int			vm_cmd(t_vm *vm, t_cmd *cmd, int chk)
{	
	if (chk < 0 || chk > 16)
		return (0);
	if (chk == 0 || chk == 8 || chk == 11 || chk == 14)
		return (1);
	else if (vm_big(vm, cmd, chk))
		return (1);
	else
		return (0);
}