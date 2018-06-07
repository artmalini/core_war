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

// int main() {

//  initscr();
//  noecho();
//  curs_set(FALSE);

//  mvprintw(0, 0, "Hello, world!");
//  refresh();

//  sleep(1);

//  endwin();
// }

int main(int argc, char **argv)
{
	int fd;
	int ret;
	int i = 0;
	char buf[BUF_SIZE + 1];
	t_player p;

	if (argc != 2)
	{
		ft_printf("error\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, buf, BUF_SIZE + 1)) > 0)
	{
		buf[ret] = '\0';
		ft_printf("%s\n", buf);
		if (i <= 1)
			p.magic = ft_strjoin(p.magic, ft_strsub(buf, 0, BUF_SIZE));
		else if (i <= PROG_NAME_LENGTH / 2 + 2)
			p.bot_name = ft_strjoin(p.bot_name, ft_strsub(buf, 0, BUF_SIZE));
		else if (i == PROG_NAME_LENGTH / 2 + 4)
			p.size_exec = ft_atoi(buf); //здесь должно быть переведение з 16 в 10 систему, но пока просто атои
		else if (i <= PROG_NAME_LENGTH / 2 + 4 + COMMENT_LENGTH / 2)
			p.comment = ft_strjoin(p.comment, ft_strsub(buf, 0, BUF_SIZE));
		else if (i >  PROG_NAME_LENGTH / 2 + 4 + COMMENT_LENGTH / 2 + 1)
			p.ex_code = ft_strjoin(p.ex_code, ft_strsub(buf, 0, BUF_SIZE));
		i++;
	}
	return (0);
}