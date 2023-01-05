/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:30:48 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/21 16:25:23 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_info(t_info *info)
{
	info->align = 0;
	info->pos = 0;
	info->blank = 0;
	info->sharp = 0;
	info->zero = 0;
	info->width = 0;
	info->dot = 0;
	info->prec = 0;
	info->spec = 0;
	info->data_len = 0;
	info->space_len = 0;
	info->zero_len = 0;
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	t_info		info;

	init_info(&info);
	info.printed_len = 0;
	va_start(ap, str);
	parse_hub(ap, (char *)str, &info);
	va_end(ap);
	return (info.printed_len);
}
