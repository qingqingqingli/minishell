/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hexa_upper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/19 18:08:59 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/08 16:58:14 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hexa_upper_output(t_format *format, va_list arguments)
{
	unsigned int	value;

	value = va_arg(arguments, unsigned int);
	if (value == 0 && format->width == 0 && format->precision == 0)
	{
		write_function('0', format);
		return ;
	}
	if (format->precision == 1 && format->precision_nb == 0 && value == 0)
	{
		number_zero(format);
		return ;
	}
	if (format->min_flag == 1)
		min_flag_xx(format, value);
	else if (format->zero_flag == 1)
		zero_flag_xx(format, value);
	else
		no_flag_xx(format, value);
}

void	min_flag_xx(t_format *format, unsigned int value)
{
	int				len;
	int				i;

	i = 0;
	len = hex_len(value);
	while (i < (format->precision_nb - len))
	{
		write_function('0', format);
		i++;
	}
	ft_puthex_upper(value, format);
	while (i < (format->width - len))
	{
		write_function(' ', format);
		i++;
	}
}

void	zero_flag_xx(t_format *format, unsigned int value)
{
	int				len;
	int				i;

	i = 0;
	len = hex_len(value);
	format->precision_nb = (format->precision_nb < len) ? len :
							format->precision_nb;
	while (i < (format->width - format->precision_nb))
	{
		if (format->precision == 0)
			write_function('0', format);
		else
			write_function(' ', format);
		i++;
	}
	i = len;
	while (i < (format->precision_nb))
	{
		write_function('0', format);
		i++;
	}
	ft_puthex_upper(value, format);
}

void	no_flag_xx(t_format *format, unsigned int value)
{
	int				len;
	int				i;

	i = 0;
	len = hex_len(value);
	format->precision_nb = (format->precision_nb < len) ? len :
							format->precision_nb;
	while (i < (format->width - format->precision_nb))
	{
		write_function(' ', format);
		i++;
	}
	i = 0;
	while (i < (format->precision_nb - len))
	{
		write_function('0', format);
		i++;
	}
	ft_puthex_upper(value, format);
}

void	ft_puthex_upper(unsigned int value, t_format *format)
{
	unsigned int	division;
	char			hex[100];
	int				number;

	number = 0;
	if (value == 0)
		write_function('0', format);
	while (value != 0)
	{
		division = value % 16;
		if (division < 10)
			hex[number] = 48 + division;
		else
			hex[number] = 55 + division;
		number++;
		value = value / 16;
	}
	number--;
	while (hex[number] > 0)
	{
		write_function(hex[number], format);
		number--;
	}
}
