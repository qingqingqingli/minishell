/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/19 13:41:03 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/06 19:50:51 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	string_output(t_format *format, va_list arguments)
{
	if (format->precision == 1 && format->precision_nb == 0 &&
		format->width == 0)
		return ;
	if (format->min_flag == 1)
		min_flag_s(format, arguments);
	else
		no_flag_s(format, arguments);
}

void	min_flag_s(t_format *format, va_list arguments)
{
	char	*string;
	int		len;
	int		i;

	i = 0;
	string = va_arg(arguments, char*);
	len = (!string) ? 6 : ft_strlenn(string);
	len = (format->precision == 0 || len < format->precision_nb) ?
			len : format->precision_nb;
	if (!string)
		ft_putstr("(null)", len, format);
	else
		ft_putstr(string, len, format);
	while (i < (format->width - len))
	{
		write_function(' ', format);
		i++;
	}
}

void	no_flag_s(t_format *format, va_list arguments)
{
	char	*string;
	int		len;
	int		i;

	i = 0;
	string = va_arg(arguments, char*);
	len = (!string) ? 6 : ft_strlenn(string);
	len = (format->precision == 0 || len < format->precision_nb) ?
			len : format->precision_nb;
	while (i < (format->width - len))
	{
		write_function(' ', format);
		i++;
	}
	if (!string)
		ft_putstr("(null)", len, format);
	else
		ft_putstr(string, len, format);
}
