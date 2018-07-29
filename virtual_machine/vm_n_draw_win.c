
#include "vm.h"

void		vm_n_draw_win3(int j)
{
	if (j == 39)
		printw("\t #     # ### #    #");
	if (j == 40)
		printw("\t #  #  #  #  ##   #");
	if (j == 41)
		printw("\t #  #  #  #  # #  #");
	if (j == 42)
		printw("\t #  #  #  #  #  # #");
	if (j == 43)
		printw("\t  ## ##  ### #   ##");
	}

void		vm_n_draw_win2(int j)
{
	if (j == 33)
		printw("\t #     # ### #    #");
	if (j == 34)
		printw("\t #  #  #  #  ##   #");
	if (j == 35)
		printw("\t #  #  #  #  # #  #");
	if (j == 36)
		printw("\t #  #  #  #  #  # #");
	if (j == 37)
		printw("\t  ## ##  ### #   ##");
}

void		vm_n_draw_win1(int j)
{
	if (j == 27)
		printw("\t #     # ### #    #");
	if (j == 28)
		printw("\t #  #  #  #  ##   #");
	if (j == 29)
		printw("\t #  #  #  #  # #  #");
	if (j == 30)
		printw("\t #  #  #  #  #  # #");
	if (j == 31)
		printw("\t  ## ##  ### #   ##");
}

void		vm_n_draw_win(int j, int pl)
{
	if (pl == 0)
	{
		if (j == 21)
			printw("\t #     # ### #    #");
		if (j == 22)
			printw("\t #  #  #  #  ##   #");
		if (j == 23)
			printw("\t #  #  #  #  # #  #");
		if (j == 24)
			printw("\t #  #  #  #  #  # #");
		if (j == 25)
			printw("\t  ## ##  ### #   ##");
	}
	if (pl == 1)
		vm_n_draw_win1(j);
	if (pl == 2)
		vm_n_draw_win2(j);
	if (pl == 3)
		vm_n_draw_win3(j);
}