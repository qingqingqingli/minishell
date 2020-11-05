/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 09:08:53 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:57:02 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		interger_len(int n)
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

static char		*create_string(char *string, int n, int i, int size)
{
	if (n == -2147483648)
	{
		string[0] = '-';
		string[1] = '2';
		n = 147483648;
	}
	if (n == 0)
	{
		string[0] = '0';
		string[1] = '\0';
	}
	if (n < 0)
	{
		n = n * -1;
		string[0] = '-';
	}
	while (n != 0)
	{
		string[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	string[size] = '\0';
	return (string);
}

char			*ft_itoa(int n)
{
	char	*string;
	int		i;
	int		size;

	size = interger_len(n);
	i = size - 1;
	string = malloc(sizeof(char) * (size + 1));
	if (!string)
		return (0);
	return (create_string(string, n, i, size));
}
