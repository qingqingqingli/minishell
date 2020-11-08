/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/19 17:30:51 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/08 16:58:14 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hex_len(unsigned long value)
{
	int				division;
	int				number;

	number = 0;
	division = 0;
	if (value == 0 && division == 0)
		return (1);
	while (value != 0)
	{
		division = value % 16;
		number++;
		value = value / 16;
	}
	return (number);
}

int		integer_len(long long n)
{
	int count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	write_negative_function(int *sign, t_format *format)
{
	int output;

	output = write(1, "-", 1);
	if (format->output == -1 || output == -1)
	{
		format->output = -1;
		return ;
	}
	format->output += output;
	*sign = 2;
}

void	number_zero(t_format *format)
{
	int i;
	int output;

	i = 0;
	while (i < format->width)
	{
		output = write(1, " ", 1);
		if (format->output == -1 || output == -1)
		{
			format->output = -1;
			return ;
		}
		format->output += output;
		i++;
	}
}
