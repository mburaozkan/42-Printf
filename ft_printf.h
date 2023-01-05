/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:30:16 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/21 18:17:13 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_info
{
	int			align;
	int			pos;
	int			blank;
	int			sharp;
	int			zero;
	int			width;
	int			dot;
	int			prec;
	int			spec;
	int			data_len;
	int			space_len;
	int			zero_len;
	int			printed_len;
}				t_info;

void			init_info(t_info *info);
int				ft_printf(const char *str, ...);
void			parse_hub(va_list ap, char *str, t_info *info);
void			print_hub(va_list ap, t_info *info);
void			ft_putchar(char c, t_info *info);
void			ft_putstr(char *s, t_info *info);
void			ft_putnbr_base(long long n, char *base, t_info *info);
int				ft_strlen(char *str, t_info *info);
int				ft_nbrlen_base(long long n, char *base, t_info *info);
void			print_space(t_info *info, long long data);
void			print_zero(t_info *info, long long data);

#endif
