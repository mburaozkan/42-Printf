/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_zero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:20:51 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/21 18:24:13 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_zero(t_info *info, long long data)
{
	if (info->spec == 's' || info->spec == 'c' || info->spec == '%')
	{
		if (info->zero && !info->align)
			info->zero_len = info->width - info->data_len;
	}
	else
	{
		if (info->zero && !info->dot && !info->prec)
		{
			info->zero_len = info->width - info->data_len - info->pos;
			if (data < 0)
				info->zero_len--;
		}
		else
			info->zero_len = info->prec - info->data_len - info->pos;
	}
	info->zero_len -= info->pos + info->blank;
	if (info->pos && data >= 0 && info->zero
		&& (info->spec == 'd' || info->spec == 'i'))
		ft_putchar('+', info);
	if (info->blank && info->zero && !info->pos && data >= 0
		&& (info->spec == 'd' || info->spec == 'i'))
		ft_putchar(' ', info);
	while (info->zero_len-- > 0)
		ft_putchar('0', info);
}
