/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:51:10 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/15 17:32:59 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_space(t_params *params, long long data)
{
	if (params->spec == 's' || params->spec == 'c' || params->spec == '%')
	{
		if (params->zero && !params->align && !params->dot && !params->prec)
			return ;
		if (params->prec && params->prec < params->data_len)
			params->space_len = params->width - params->prec;
		else
			params->space_len = params->width - params->data_len;
	}
	else
	{
		if (params->data_len < params->prec)
			params->space_len = params->width - params->prec;
		else
			params->space_len = params->width - params->data_len;
		if (data < 0)
			params->space_len--;
		if (params->spec == 'p')
			params->space_len -= 2;
		if (params->zero && !params->dot && !params->prec)
			params->space_len -= params->width - params->data_len;
	}
	while (params->space_len-- > 0)
		ft_putchar(' ', params);
}

static void	print_zero(t_params *params, long long data)
{
	if (params->spec == 's' || params->spec == 'c' || params->spec == '%')
	{
		if (params->zero && !params->align)
			params->zero_len = params->width - params->data_len;
	}
	else
	{
		if (params->zero && !params->dot && !params->prec)
		{
			params->zero_len = params->width - params->data_len;
			if (data < 0)
				params->zero_len--;
		}
		else
			params->zero_len = params->prec - params->data_len;
	}
	while (params->zero_len-- > 0)
		ft_putchar('0', params);
}

static void	print_diuxp_ifs(long long data, t_params *params, char *base)
{
	if (data < 0)
		params->data_len = ft_nbrlen_base(-1 * data, base, params);
	else
		params->data_len = ft_nbrlen_base(data, base, params);
	if (params->align == 0)
		print_space(params, data);
	if (data < 0)
		ft_putchar('-', params);
	if (params->spec == 'p')
		ft_putstr("0x", params);
	print_zero(params, data);
	if (data < 0)
		ft_putnbr_base(-1 * data, base, params);
	else
		ft_putnbr_base(data, base, params);
	if (params->align == 1)
		print_space(params, data);
}

static void	print_diuxp(va_list ap, t_params *params)
{
	char			*base;
	long long		data;

	if (params->spec == 'd' || params->spec == 'i')
		data = va_arg(ap, int);
	else if (params->spec == 'u' || params->spec == 'x' || params->spec == 'X')
		data = va_arg(ap, unsigned int);
	else
		data = va_arg(ap, unsigned long);
	if (params->spec == 'd' || params->spec == 'i' || params->spec == 'u')
		base = "0123456789";
	else if (params->spec == 'X')
		base = "0123456789ABCDEF";
	else if (params->spec == 'x')
		base = "0123456789abcdef";
	print_diuxp_ifs(data, params, base);
}

static void	print_sc(va_list ap, t_params *params)
{
	char			*data_s;
	int				data_c;

	data_s = 0;
	data_c = 0;
	if (params->spec == 's')
		data_s = va_arg(ap, char *);
	else if (params->spec == 'c')
		data_c = va_arg(ap, int);
	else
		data_c = '%';
	if (data_s == NULL)
		data_s = "(null)";
	if (params->spec == 's')
		params->data_len = ft_strlen(data_s, params);
	if (params->align == 0)
		print_space(params, 0);
	print_zero(params, 0);
	if (params->spec == 's')
		ft_putstr(data_s, params);
	else
		ft_putchar(data_c, params);
	if (params->align == 1)
		print_space(params, 0);
}

void	print_hub(va_list ap, t_params *params)
{
	if (params->spec == 'd' || params->spec == 'i' || params->spec == 'u'
		|| params->spec == 'x' || params->spec == 'X' || params->spec == 'p')
		print_diuxp(ap, params);
	else if (params->spec == 's' || params->spec == 'c' || params->spec == '%')
		print_sc(ap, params);
}
