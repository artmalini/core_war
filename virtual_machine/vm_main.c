/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:06:48 by tvertohr          #+#    #+#             */
/*   Updated: 2018/06/06 11:06:49 by tvertohr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// void	draw_dead_pl(int j)
// {
// ##  ### ##  
// # #  #  # # 
// ##   #  ##  
// # #  #  #   
// # # ### #
// }


/*int		vm_its_cmd(t_vm *vm, t_cmd *cmd)
{
	int		i;
	// int		a;
	// int 	b;


	////vm->arena[cmd->idx].pl = cmd->pl;
	i = 0;
	// if (vm->arena[mdx(cmd->idx)].hit == 1)
	// {
	// 	if (a != b)
 //        {
 //            if ((b - 1 >= 0 && b - 1 < 16) && (vm->arena[cmd->idx].pl != cmd->pl))
	// 		    vm->arena[mdx(cmd->idx)].acb = vm->arena[mdx(cmd->idx)].o_acb;
 //        }
	// }
		i = (vm->arena[mdx(cmd->idx)].acb & 0xFF) - 1;
	if (i < 0 || i > 16)
		return (0);
	else		
		return (1);	
}*/


int			main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc < 2)
		vm_usage();
	vm = ft_memalloc(sizeof(t_vm));
	vm->last_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm_init(vm);
	vm_create_arena(vm);
	if (vm_get_param(argv, vm, argc) == 0)
		vm_exit(vm);
	vm_load_champs(vm);
	vm_load_lists(&vm->cmd, vm);
	vm_glow_cur(vm, vm->cmd);
	//нужно дописать функцию самой игры и реализовать функции
	if (vm->visual && vm->dump_cycle == -1)
		vm_load_ncurses();
	vm_load_arena(vm);
	if (vm->visual && vm->dump_cycle == -1)
	{
		getch();
		endwin();
	}
	vm_winner(vm);
	//ft_printf("main vm->tab_champ[0].weight %d\n", vm->tab_champ[0].weight);
	free_vm(vm);
	return (0);
}
