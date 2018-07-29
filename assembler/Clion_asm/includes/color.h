/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakahon <vmakahon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:04:00 by vmakahon          #+#    #+#             */
/*   Updated: 2018/07/03 19:04:00 by vmakahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

/*
**					[Macros for Standard Color]
*/

# define RESET  	"\033[0m"
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define GRAY		"\033[0;37m"

/*
**					[Macros for Bold Color]
*/

# define DEF		"\033[0;39m"
# define DGRAY		"\033[1;30m"
# define LRED		"\033[1;31m"
# define LGREEN		"\033[1;32m"
# define LYELLOW	"\033[1;33m"
# define LBLUE		"\033[1;34m"
# define LMAGENTA	"\033[1;35m"
# define LCYAN		"\033[1;36m"
# define LWHITE		"\033[1;37m"

/*
**					[Macros for BackGround Color]
*/

# define BGBLACK	"\033[40m"
# define BGRED		"\033[41m"
# define BGGREEN	"\033[42m"
# define BGBROWN	"\033[43m"
# define BGBLUE		"\033[44m"
# define BGMAGENTA	"\033[45m"
# define BGCYAN		"\033[46m"
# define BGGRAY		"\033[47m"
# define BGDEF		"\033[49m"

#endif
