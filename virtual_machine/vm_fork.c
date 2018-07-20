
#include "vm.h"

void		fork_update_reg(int *dest, int *host)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
		dest[i] = host[i];
}

t_cmd		*fork_add_list(t_cmd *cmd1, int nb)
{
	t_cmd	*lst;

	lst = NULL;
	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst)
	{
		fork_update_reg(lst->reg, cmd1->reg);
		lst->idx = cmd1->idx;
		lst->rgb = cmd1->rgb;
		lst->playing = 0;
		lst->wait = 0;
		lst->on = 0;
		lst->off = 0;
		lst->carry = cmd1->carry;
		lst->life = 1;
		lst->nbr_process = nb;
		lst->flag = 0;
		lst->next = NULL;
	}	
	return (lst);
}

void	vm_fork(t_vm *vm, t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*cmd1;
	//t_cmd	*cmd2;
	short	two;
	int		two_val;


	cmd1 = NULL;
	tmp = NULL;
	cmd1 = *cmd;
	//cmd2 = *cmd;
	two = 0xFF & vm->arena[mdx(cmd1->idx + 1)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd1->idx + 2)].acb;
	two_val = (two % IDX_MOD);
	if (cmd1)
	{
		tmp = fork_add_list(cmd1, vm->total_process + 1);
		if (vm->debug)
			ft_printf("|P\t%d| fork |%d| (%d)\n", cmd1->nbr_process, two_val, tmp->idx + two_val);
		//vm->tab_champ[cmd1->reg[0] - 1].nbr_process += 1;

		vm->total_process += 1;
		while (cmd1->next != NULL)
			cmd1 = cmd1->next;
		cmd1->next = tmp;

		//tmp->next = *cmd;
		//*cmd = tmp;
	}

	vm_next_step(vm, *cmd, 3);
	vm_next_step(vm, tmp, two_val);
}
