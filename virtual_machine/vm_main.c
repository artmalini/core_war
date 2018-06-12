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
#include <fcntl.h>

// int main() {

//  initscr();
//  noecho();
//  curs_set(FALSE);

//  mvprintw(0, 0, "Hello, world!");
//  refresh();

//  sleep(1);

//  endwin();
// }

void	ft_error(char *name)
{
	ft_printf("%s\n", name);
	exit(1);
}

// void vm_read(char *av, int fd)
// {
// 	char *
// }

int main(int argc, char **argv)
{
	int fd;
	int ret;
	//int i;
	//char buf[BUF_SIZE];
	char *line;
	//t_player p;

	if (argc == 1)
		ft_error("Not enough arguments.");
	//i = 0;
	//ft_bzero(&p, sizeof(t_player));
	line = ft_memalloc(CHAMP_MAX_SIZE);
	fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, line, CHAMP_MAX_SIZE)) > 0)
	{
		line[ret] = '\0';
		ft_printf("%s\n", line);
		// if (i <= 1)
		// 	p.magic = ft_strjoin(p.magic, ft_strsub(buf, 0, BUF_SIZE));
		// else if (i <= PROG_NAME_LENGTH / 2 + 2)
		// 	p.bot_name = ft_strjoin(p.bot_name, ft_strsub(buf, 0, BUF_SIZE));
		// else if (i == PROG_NAME_LENGTH / 2 + 4)
		// 	p.size_exec = ft_atoi_base(buf, 16); //здесь должно быть переведение з 16 в 10 систему, но пока просто атои
		// else if (i <= PROG_NAME_LENGTH / 2 + 4 + COMMENT_LENGTH / 2)
		// 	p.comment = ft_strjoin(p.comment, ft_strsub(buf, 0, BUF_SIZE));
		// else if (i >  PROG_NAME_LENGTH / 2 + 4 + COMMENT_LENGTH / 2 + 1)
		// 	p.ex_code = ft_strjoin(p.ex_code, ft_strsub(buf, 0, BUF_SIZE));
		// i++;
	}
	ft_memdel((void**)&line);
	return (0);
}