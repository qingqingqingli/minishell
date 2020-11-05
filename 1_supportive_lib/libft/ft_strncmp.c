/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:51:20 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:59:03 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t count;

	count = 1;
	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && (count < n))
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
		count++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
