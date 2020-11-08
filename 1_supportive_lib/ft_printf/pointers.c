/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pointers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 15:33:35 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/08 16:58:14 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pointer_output(t_format *format, va_list arguments)
{
	if (format->min_flag == 1)
		min_flag_p(format, arguments);
	else
		no_flag_p(format, arguments);
}

void	min_flag_p(t_format *format, va_list arguments)
{
	void	*value;
	int		len;
	int		i;

	i = 0;
	value = va_arg(arguments, void*);
	len = (format->precision == 1 && format->precision_nb != 0) ? 2 :
			hex_len((unsigned long)value) + 2;
	len = (format->precision == 1 && value == 0) ? 2 :
			hex_len((unsigned long)value) + 2;
	write_function('0', format);
	write_function('x', format);
	if (format->precision_nb != 1)
	{
		ft_puthex_lower((unsigned long)value, format);
	}
	while (i < (format->width - len))
	{
		write_function(' ', format);
		i++;
	}
}

void	no_flag_p(t_format *format, va_list arguments)
{
	void			*value;
	int				len;
	int				i;

	i = 0;
	value = va_arg(arguments, void*);
	len = (format->precision == 1 && format->precision_nb != 0) ? 2 :
			hex_len((unsigned long)value) + 2;
	len = (format->precision == 1 && value == 0) ? 2 :
			hex_len((unsigned long)value) + 2;
	while (i < (format->width - len))
	{
		write_function(' ', format);
		i++;
	}
	write_function('0', format);
	write_function('x', format);
	if ((format->precision == 1 && format->precision_nb != 0) ||
		(format->precision == 1 && value == 0))
		return ;
	else
		ft_puthex_lower((unsigned long)value, format);
}
