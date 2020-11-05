/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 15:37:05 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:59:26 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	size;

	if (!s)
		return (0);
	size = ft_strlen(s);
	i = 0;
	if (start > size)
		return (ft_strdup(""));
	if ((start + len) <= size)
		substr = malloc(sizeof(char) * (len + 1));
	else
		substr = malloc(sizeof(char) * (size - start + 1));
	if (!substr)
		return (0);
	while ((i < len) && (s[start + i] != '\0'))
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
