/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 14:34:02 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/26 15:56:29 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long int i;
	long long int neg;
	long long int output;

	i = 0;
	neg = 1;
	output = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		neg = neg * -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (output * 10 + str[i] - '0' < output && neg == 1)
			return (0);
		if (output * 10 + str[i] - '0' < output && neg == -1)
			return (0);
		output = output * 10 + str[i] - '0';
		i++;
		if (str[i] < '0' || str[i] > '9')
			return ((int)output * neg);
	}
	return ((int)output * neg);
}
