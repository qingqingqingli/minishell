/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scan_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 10:47:02 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/06 19:50:51 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	scan_specifier(const char *str, int *spot, t_format *format, int count)
{
	while (str[*spot + count] != ' ' && str[*spot + count] != '\0')
	{
		if (str[*spot] == 'c')
			format->specifier = 'c';
		if (str[*spot] == 's')
			format->specifier = 's';
		if (str[*spot] == 'p')
			format->specifier = 'p';
		if (str[*spot] == 'd' || str[*spot] == 'i')
			format->specifier = 'd';
		if (str[*spot] == 'u')
			format->specifier = 'u';
		if (str[*spot] == 'x')
			format->specifier = 'x';
		if (str[*spot] == 'X')
			format->specifier = 'X';
		if (str[*spot] == '%')
			format->specifier = '%';
		if (specifier_checker(str, spot, 0))
			break ;
		*spot = *spot + 1;
	}
	if (format->specifier != 0)
		*spot = *spot + 1;
}

void	scan_wildcard(const char *str, int *spot, t_format *format,
						va_list arguments)
{
	int count;

	count = 0;
	while (!specifier_checker(str, spot, count))
	{
		if (str[*spot + count] == '*' && str[*spot + count - 1] != '.')
			format->width = va_arg(arguments, int);
		if (str[*spot + count] == '.')
		{
			count++;
			if (str[*spot + count] == '*')
				format->precision_nb = va_arg(arguments, int);
			while (str[*spot + count] >= '0' && str[*spot + count] <= '9')
			{
				format->precision_nb = (format->precision_nb * 10) +
										str[*spot + count] - '0';
				count++;
			}
		}
		count++;
	}
}

void	handeling_negatives(t_format *format)
{
	format->precision = (format->precision_nb < 0) ? 0 : format->precision;
	format->precision_nb = (format->precision_nb < 0) ? 0 :
							format->precision_nb;
	format->min_flag = (format->width < 0) ? 1 : format->min_flag;
	format->width = (format->width < 0) ? format->width * -1 : format->width;
}

void	scan_flags(const char *str, int *spot, t_format *format, int count)
{
	while (!specifier_checker(str, spot, count))
	{
		if (str[*spot + count] == '0' && (str[*spot + count - 1] < '0' ||
			str[*spot + count - 1] > '9'))
		{
			format->zero_flag = 1;
			count++;
		}
		if (str[*spot + count] == '-')
			format->min_flag = 1;
		if (str[*spot + count] == '.')
			format->precision = 1;
		while (format->precision != 1 && str[*spot + count] >= '0' &&
				str[*spot + count] <= '9')
		{
			format->width = (format->width * 10) + str[*spot + count] - '0';
			if (str[*spot + count + 1] >= '0' && str[*spot + count + 1] <= '9')
				count++;
			else
				break ;
		}
		count++;
	}
}
