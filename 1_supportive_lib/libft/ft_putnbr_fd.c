/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 13:38:08 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:57:56 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putchar_fd(('-'), fd);
			ft_putchar_fd(('2'), fd);
			n = 147483648;
		}
		else
		{
			ft_putchar_fd(('-'), fd);
			n = n * -1;
		}
	}
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
	}
	ft_putchar_fd(('0' + (n % 10)), fd);
}
