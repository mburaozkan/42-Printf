/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:20:32 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/21 18:24:06 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_space_part1(t_info *info, long long data)
{
	if (info->spec == 's' || info->spec == 'c' || info->spec == '%')
	{
		if (info->zero && !info->align && !info->dot && !info->prec)
			return ;
		if (info->prec && info->prec < info->data_len)
			info->space_len = info->width - info->prec;
		else
			info->space_len = info->width - info->data_len;
	}
	else
	{
		if (info->data_len < info->prec)
			info->space_len = info->width - info->prec;
		else
			info->space_len = info->width - info->data_len;
		if (data < 0 || info->pos)
			info->space_len--;
		if (info->spec == 'p')
			info->space_len -= 2;
		if (info->zero && !info->dot && !info->prec)
			info->space_len -= info->width - info->data_len;
	}
}

void	print_space(t_info *info, long long data)
{
	print_space_part1(info, data);
	while (info->space_len-- > 0)
		ft_putchar(' ', info);
	if (info->pos && !info->zero && data >= 0
		&& (info->spec == 'd' || info->spec == 'i'))
		ft_putchar('+', info);
	if (info->blank && !info->zero && !info->pos && data >= 0
		&& (info->spec == 'd' || info->spec == 'i'))
		ft_putchar(' ', info);
}
