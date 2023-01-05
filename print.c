/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:51:10 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/21 18:23:32 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	select_base(t_info *info, char *base)
{
	if (info->spec == 'd' || info->spec == 'i' || info->spec == 'u')
		base = "0123456789";
	else if (info->spec == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
}

static void	select_data_len(t_info *info, char *base, long long data)
{
	if (data < 0)
		info->data_len = ft_nbrlen_base(-1 * data, base, info);
	else
		info->data_len = ft_nbrlen_base(data, base, info);
}

static void	print_diuxp(t_info *info, long long data)
{
	char			*base;

	select_base(info, base);
	select_base(info, base, data);
	if (info->align == 0)
		print_space(info, data);
	if (data < 0)
		ft_putchar('-', info);
	if (info->spec == 'p')
		ft_putstr("0x", info);
	if (info->sharp && data != 0)
	{
		if (info->spec == 'X')
			ft_putstr("0X", info);
		else if (info->spec == 'x')
			ft_putstr("0x", info);
	}
	print_zero(info, data);
	if (data < 0)
		ft_putnbr_base(-1 * data, base, info);
	else
		ft_putnbr_base(data, base, info);
	if (info->align == 1)
		print_space(info, data);
}

static void	print_sc(va_list ap, t_info *info)
{
	char			*data_s;
	int				data_c;

	data_s = 0;
	data_c = 0;
	if (info->spec == 's')
		data_s = va_arg(ap, char *);
	else if (info->spec == 'c')
		data_c = va_arg(ap, int);
	else
		data_c = '%';
	if (data_s == NULL)
		data_s = "(null)";
	if (info->spec == 's')
		info->data_len = ft_strlen(data_s, info);
	if (info->align == 0)
		print_space(info, 0);
	print_zero(info, 0);
	if (info->spec == 's')
		ft_putstr(data_s, info);
	else
		ft_putchar(data_c, info);
	if (info->align == 1)
		print_space(info, 0);
}

void	print_hub(va_list ap, t_info *info)
{
	long long		data;
	unsigned long	ul_data;

	info->data_len = 1;
	if (info->spec == 'd' || info->spec == 'i' || info->spec == 'u'
		|| info->spec == 'x' || info->spec == 'X' || info->spec == 'p')
	{
		if (info->spec == 'd' || info->spec == 'i')
			data = va_arg(ap, int);
		else if (info->spec == 'u' || info->spec == 'x' || info->spec == 'X')
			data = va_arg(ap, unsigned int);
		else
		{
			data = va_arg(ap, unsigned long long);
			ul_data = data;
		}
		if (data == LONG_MIN)
			info->printed_len += ft_printf("%s", "0x8000000000000000");
		else if (ul_data == ULONG_MAX)
			info->printed_len += ft_printf("%s", "0xffffffffffffffff");
		else
			print_diuxp(info, data);
	}
	else if (info->spec == 's' || info->spec == 'c' || info->spec == '%')
		print_sc(ap, info);
}
