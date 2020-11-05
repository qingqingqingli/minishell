/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 11:05:05 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:57:34 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;
	size_t n;

	i = 0;
	n = len;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		if ((char*)src < (char*)dst)
		{
			((char*)dst)[len - 1] = ((char*)src)[len - 1];
			len--;
		}
		else
			((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst);
}
