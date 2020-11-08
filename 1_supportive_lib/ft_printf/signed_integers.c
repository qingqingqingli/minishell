/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signed_integers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 11:36:59 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/06 19:50:51 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	signed_integer_output(t_format *format, va_list arguments, int sign)
{
	int value;

	value = va_arg(arguments, int);
	if (format->precision == 1 && format->precision_nb == 0 && value == 0)
	{
		number_zero(format);
		return ;
	}
	if (value < 0)
	{
		value = value * -1;
		sign = 1;
		if (((format->width < integer_len(value)) && format->precision_nb == 0)
			|| (format->zero_flag == 1 && format->precision == 0))
			write_negative_function(&sign, format);
	}
	if (format->min_flag == 1)
		min_flag_d_i(format, value, sign);
	else if (format->zero_flag == 1)
		zero_flag_d_i(format, value, sign);
	else
		no_flag_d_i(format, value, sign);
}

void	min_flag_d_i(t_format *format, int value, int sign)
{
	int len;
	int i;

	i = 0;
	len = (value != -2147483648) ? integer_len(value) : integer_len(value) - 1;
	format->width = (sign) ? format->width - 1 : format->width;
	if (sign == 1)
		write_function('-', format);
	while (i < (format->precision_nb - len))
	{
		write_function('0', format);
		i++;
	}
	ft_putnbr(value, format);
	while (i < (format->width - len))
	{
		write_function(' ', format);
		i++;
	}
}

void	zero_flag_d_i(t_format *format, int value, int sign)
{
	int i;
	int len;

	i = 0;
	len = (value != -2147483648) ? integer_len(value) : integer_len(value) - 1;
	format->width = (sign) ? format->width - 1 : format->width;
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
	i = integer_len(value);
	if (sign == 1)
		write_function('-', format);
	while (i < (format->precision_nb))
	{
		write_function('0', format);
		i++;
	}
	ft_putnbr(value, format);
}

void	no_flag_d_i(t_format *format, int value, int sign)
{
	int i;
	int	len;
	int reset;

	len = (value != -2147483648) ? integer_len(value) : integer_len(value) - 1;
	reset = (format->precision_nb > len) ? format->precision_nb - len : 0;
	i = 0;
	format->width = (sign) ? format->width - 1 : format->width;
	while (i < (format->width - len - reset))
	{
		write_function(' ', format);
		i++;
	}
	i = 0;
	if (sign == 1)
		write_function('-', format);
	while (i < (format->precision_nb - len))
	{
		write_function('0', format);
		i++;
	}
	ft_putnbr(value, format);
}
