/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:44:13 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/21 16:26:10 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flag(char **str, t_info *info)
{
	while (**str == '-' || **str == '0' || **str == '+'
		|| **str == ' ' || **str == '#')
	{
		if (**str == '-')
			info->align = 1;
		if (**str == '0')
			info->zero = 1;
		if (**str == '+')
			info->pos = 1;
		if (**str == ' ')
			info->blank = 1;
		if (**str == '#')
			info->sharp = 1;
		(*str)++;
	}
	if (info->align && info->zero)
		info->zero = 0;
}

static void	parse_width(va_list ap, char **str, t_info *info)
{
	if (**str == '*')
	{
		info->width = va_arg(ap, int);
		if (info->width < 0)
		{
			if (info->zero)
				info->zero = 0;
			info->width *= -1;
			info->align = 1;
		}
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		info->width = (info->width * 10) + **str - '0';
		(*str)++;
	}
}

static void	parse_precision(va_list ap, char **str, t_info *info)
{
	if (**str == '.')
	{
		info->dot = 1;
		(*str)++;
	}
	if (**str == '*')
	{
		info->prec = va_arg(ap, int);
		if (info->prec < 0)
		{
			info->prec = 0;
			info->dot = 0;
		}
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		info->prec = (info->prec * 10) + **str - '0';
		(*str)++;
	}
}

static void	parse_specifier(char **str, t_info *info)
{
	if (**str == 'c' || **str == 's' || **str == 'p' || **str == 'd'
		|| **str == 'i' || **str == 'u' || **str == 'x' || **str == 'X'
		|| **str == '%')
		info->spec = **str;
	else
		return ;
	(*str)++;
}

void	parse_hub(va_list ap, char *str, t_info *info)
{
	while (*str)
	{
		if (*str == '%')
		{
			++str;
			parse_flag(&str, info);
			parse_width(ap, &str, info);
			parse_precision(ap, &str, info);
			parse_specifier(&str, info);
			print_hub(ap, info);
			init_info(info);
		}
		else
			ft_putchar(*(str)++, info);
	}
}
