/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 19:21:07 by amakhiny          #+#    #+#             */
/*   Updated: 2018/01/19 19:21:12 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>

typedef struct		s_bone
{
	int				mod_l;
	char			type;
	char			*hex;
	char			padding;
	int				base;
	int				prefix;
	int				left;
	int				flag;
	int				width;
	int				minus;
	int				precis;
	int				sign;
	unsigned short	xx;
}					t_bone;

int					ft_printf(const char *format, ...);
void				fill_flag(const char **f, t_bone *elem);
void				fill_width(const char **format, va_list arg, t_bone *elem);
void				fill_precis(const char **format, va_list arg, t_bone *elem);
void				fill_length(const char **format, t_bone *elem);
void				fill_type(const char **format, t_bone *elem);
void				fill_hex(const char **format, t_bone *elem);
int					chk_o_min(t_bone *elem);
int					parse_arg(va_list arg, t_bone *elem, int ln);
char				*build_char(va_list arg, t_bone *elem);
char				*build_str_char(va_list arg, t_bone *elem);
char				*ft_strlendup(const char *str1, int len);
char				*prf_itoa_base(t_bone *elem, uintmax_t bighigh, int len);
uintmax_t			uintmax_cast(uintmax_t nbr, t_bone *elem);
intmax_t			intmax_cast(uintmax_t nbr, t_bone *elem);
void				prf_print_str_ln(char *str, int nbr);
void				hex_free(t_bone *elem);
int					prf_putchar(char c);
int					prf_nbr_putchar(char c, int nbr);
int					prf_putstr(char *str);
int					ft_char(char *str);
char				*build_float_join_str(t_bone *elem, long double nbr);
int					print_floate_nbr(va_list arg, t_bone *elem);
char				*build_mantissa(t_bone *elem, long double nbr, \
					long double val);
long double			build_float(t_bone *elem, long double droby);
int					print_atoi_nbr(va_list arg, t_bone *elem);
int					print_str_with_flags(char *str, t_bone *elem, int str_len);
char				*str_join_float(char *str1, char *str2);
char				*ft_strlendup(const char *str1, int len);

int					g_flag;

#endif
