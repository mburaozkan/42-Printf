/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miozkan <miozkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:25:11 by miozkan           #+#    #+#             */
/*   Updated: 2022/10/15 16:25:12 by miozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_diuxp_ifs(long long data, t_params *params, char *base)
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