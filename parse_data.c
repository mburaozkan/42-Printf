/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:51:08 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/15 15:58:09 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flag(char **str, t_params *params)
{
	while (**str == '-' || **str == '0')
	{
		if (**str == '-')
			params->align = 1;
		if (**str == '0')
			params->zero = 1;
		(*str)++;
	}
	if (params->align && params->zero)
		params->zero = 0;
}

static void	parse_width(va_list ap, char **str, t_params *params)
{
	if (**str == '*')
	{
		params->width = va_arg(ap, int);
		if (params->width < 0)
		{
			if (params->zero)
				params->zero = 0;
			params->width *= -1;
			params->align = 1;
		}
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		params->width = (params->width * 10) + **str - '0';
		(*str)++;
	}
}

static void	parse_precision(va_list ap, char **str, t_params *params)
{
	if (**str == '.')
	{
		params->dot = 1;
		(*str)++;
	}
	if (**str == '*')
	{
		params->prec = va_arg(ap, int);
		if (params->prec < 0)
		{
			params->prec = 0;
			params->dot = 0;
		}
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		params->prec = (params->prec * 10) + **str - '0';
		(*str)++;
	}
}

static void	parse_specifier(char **str, t_params *params)
{
	if (**str == 'c' || **str == 's' || **str == 'p' || **str == 'd'
		|| **str == 'i' || **str == 'u' || **str == 'x' || **str == 'X'
		|| **str == '%')
		params->spec = **str;
	else
		return ;
	(*str)++;
}

void	parse_hub(va_list ap, char *str, t_params *params)
{
	while (*str)
	{
		if (*str == '%')
		{
			++str;
			parse_flag(&str, params);
			parse_width(ap, &str, params);
			parse_precision(ap, &str, params);
			parse_specifier(&str, params);
			print_hub(ap, params);
			params_reset(params);
		}
		else
			ft_putchar(*(str)++, params);
	}
}
