/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:40:22 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:59:09 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(const char *str1, const char *str2, size_t n)
{
	int i;

	i = 0;
	while (str1[i] == str2[i])
	{
		i++;
		n--;
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str2[i] == '\0')
			return (0);
		if (n == 0 && (str1[i] != '\0' && str2[i] != '\0'))
			return (1);
	}
	return (str1[i] - str2[i]);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	i = 0;
	if (needle[i] == '\0')
		return ((char*)haystack);
	if (len == 0)
		return (0);
	while (len > 0 && haystack[i] != '\0')
	{
		if (ft_compare(&haystack[i], needle, len) == 0)
			return ((char*)haystack + i);
		i++;
		len--;
	}
	return (0);
}
