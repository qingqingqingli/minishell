/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   characters.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 16:15:44 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/06 19:50:51 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	charachter_output(t_format *format, va_list arguments)
{
	if (format->min_flag == 1)
		min_flag_c(format, arguments);
	else
		no_flag_c(format, arguments);
}

void	min_flag_c(t_format *format, va_list arguments)
{
	int character;
	int i;

	i = 0;
	character = va_arg(arguments, int);
	write_function(character, format);
	while (i < (format->width - 1))
	{
		write_function(' ', format);
		i++;
	}
}

void	no_flag_c(t_format *format, va_list arguments)
{
	int character;
	int i;

	i = 0;
	character = va_arg(arguments, int);
	while (i < (format->width - 1))
	{
		write_function(' ', format);
		i++;
	}
	write_function(character, format);
}
