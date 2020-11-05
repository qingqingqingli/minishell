/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   percentage_sign.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 13:41:23 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/28 12:56:15 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	percentage_output(t_format *format)
{
	if (format->min_flag == 1)
		min_flag_perc(format);
	else if (format->zero_flag == 1)
		zero_flag_perc(format);
	else
		no_flag_perc(format);
}

void	min_flag_perc(t_format *format)
{
	int i;

	i = 0;
	while (i < (format->precision_nb - 1))
	{
		write_function('0', format);
		i++;
	}
	write_function('%', format);
	while (i < (format->width - 1))
	{
		write_function(' ', format);
		i++;
	}
}

void	zero_flag_perc(t_format *format)
{
	int i;

	i = 0;
	format->precision_nb = (format->precision_nb == 0) ? 1 :
							format->precision_nb;
	while (i < (format->width - format->precision_nb))
	{
		if (format->precision == 0)
			write_function('0', format);
		else
			write_function(' ', format);
		i++;
	}
	i = 1;
	while (i < (format->precision_nb))
	{
		write_function('0', format);
		i++;
	}
	write_function('%', format);
}

void	no_flag_perc(t_format *format)
{
	int i;

	i = 0;
	while (i < (format->width - 1))
	{
		write_function(' ', format);
		i++;
	}
	while (i < (format->precision_nb - 1))
	{
		write_function('0', format);
		i++;
	}
	write_function('%', format);
}
