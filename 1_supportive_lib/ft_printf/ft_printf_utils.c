/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 11:18:23 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/08 16:58:14 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			specifier_checker(const char *str, int *spot, int count)
{
	if (str[*spot + count] == '%' || str[*spot + count] == 'X' ||
		str[*spot + count] == 'x' || str[*spot + count] == 'u' ||
		str[*spot + count] == 'd' || str[*spot + count] == 'i' ||
		str[*spot + count] == 's' || str[*spot + count] == 'c' ||
		str[*spot + count] == 'p')
		return (1);
	else
		return (0);
}

int			ft_strlenn(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void		ft_putnbr(long long n, t_format *format)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write_function('2', format);
			n = 147483648;
		}
		else
			n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbr((n / 10), format);
	}
	write_function(('0' + (n % 10)), format);
}

void		write_function(char c, t_format *format)
{
	int output;

	output = write(1, &c, 1);
	if (format->output == -1 || output == -1)
	{
		format->output = -1;
		return ;
	}
	format->output += output;
}

void		ft_putstr(char *s, int size, t_format *format)
{
	int i;

	if (s == 0)
		return ;
	i = 0;
	while (s[i] != '\0' && i < size)
	{
		write_function(s[i], format);
		i++;
	}
}
