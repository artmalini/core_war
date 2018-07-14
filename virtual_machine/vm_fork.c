
#include "vm.h"

void		fork_update_reg(int *dest, int *host)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
		dest[i] = host[i];
}

t_cmd		*fork_add_list(t_cmd *cmd1)
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
		lst->carry = 0;
		lst->life = 1;
		lst->nbr_process = 1;
		lst->flag = 0;
		lst->next = NULL;
		//ft_printf("lst->idx |%d|", lst->idx);
	}	
	return (lst);
}

void	vm_fork(t_vm *vm, t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*cmd1;
	int		cursor;
	unsigned short	two;


	cmd1 = NULL;
	tmp = NULL;
	cursor = 0;
	cmd1 = *cmd;
	two = 0xFF & vm->arena[mdx(cmd1->idx + 1)].acb;
	two <<= 8;
	two += 0xFF & vm->arena[mdx(cmd1->idx + 2)].acb;
	cursor = two;
	if (cmd1)
	{
		tmp = fork_add_list(*cmd);
		//vm->tab_champ[cmd1->reg[0] - 1].nbr_process += 1;
		while (cmd1->next != NULL)
			cmd1 = cmd1->next;
		cmd1->next = tmp;
	}

	vm_next_step(vm, *cmd, 3);

	//ft_printf("lst->idx |%d|", mdx(cursor));
	vm_next_step(vm, tmp, mdx(cursor));
}