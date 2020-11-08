/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 15:53:47 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/08 16:58:14 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_charachters(const char *str, int *spot, t_format *format)
{
	while (str[*spot] != '\0')
	{
		if (str[*spot] != '%')
		{
			write_function(str[*spot], format);
			*spot = *spot + 1;
		}
		if (str[*spot] == '%')
			return ;
	}
	return ;
}

void	reset_struct(t_format *format)
{
	format->min_flag = 0;
	format->zero_flag = 0;
	format->width = 0;
	format->precision = 0;
	format->precision_nb = 0;
	format->specifier = 0;
}

void	reset_output(t_format *format)
{
	format->output = 0;
}

void	generate_output(t_format *format, va_list arguments)
{
	if (format->specifier == 'c')
		charachter_output(format, arguments);
	if (format->specifier == 's')
		string_output(format, arguments);
	if (format->specifier == 'p')
		pointer_output(format, arguments);
	if (format->specifier == 'd' || format->specifier == 'i')
		signed_integer_output(format, arguments, 0);
	if (format->specifier == 'u')
		unsigned_integer_output(format, arguments);
	if (format->specifier == 'x')
		hexa_lower_output(format, arguments);
	if (format->specifier == 'X')
		hexa_upper_output(format, arguments);
	if (format->specifier == '%')
		percentage_output(format);
}

int		ft_printf(const char *str, ...)
{
	int			spot;
	va_list		arguments;
	t_format	format;

	spot = 0;
	va_start(arguments, str);
	reset_output(&format);
	while (str[spot] != '\0')
	{
		if (str[spot] == '%')
		{
			spot++;
			reset_struct(&format);
			scan_flags(str, &spot, &format, 0);
			scan_wildcard(str, &spot, &format, arguments);
			scan_specifier(str, &spot, &format, 0);
			handeling_negatives(&format);
			generate_output(&format, arguments);
		}
		else
			print_charachters(str, &spot, &format);
	}
	va_end(arguments);
	return (format.output);
}
