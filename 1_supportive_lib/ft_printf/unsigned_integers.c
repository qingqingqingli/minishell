/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unsigned_integers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/19 18:55:12 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/08 16:58:14 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	unsigned_integer_output(t_format *format, va_list arguments)
{
	unsigned int	value;

	value = va_arg(arguments, unsigned int);
	if (format->precision == 1 && format->precision_nb == 0 && value == 0)
	{
		number_zero(format);
		return ;
	}
	if (format->min_flag == 1)
		min_flag_u(format, value);
	else if (format->zero_flag == 1)
		zero_flag_u(format, value);
	else
		no_flag_u(format, value);
}

void	min_flag_u(t_format *format, unsigned int value)
{
	int				len;
	int				i;

	i = 0;
	len = integer_len(value);
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

void	zero_flag_u(t_format *format, unsigned int value)
{
	int				len;
	int				i;

	i = 0;
	len = integer_len(value);
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
	ft_putnbr(value, format);
}

void	no_flag_u(t_format *format, unsigned int value)
{
	int				len;
	int				i;

	i = 0;
	len = integer_len(value);
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
	ft_putnbr(value, format);
}
