/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 15:51:57 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:58:32 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;
	int		x;

	if (s1 == 0)
		return (0);
	i = 0;
	x = 0;
	joined_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined_str)
		return (0);
	while (s1[i] != '\0')
	{
		joined_str[i] = s1[i];
		i++;
	}
	while (s2[x] != '\0')
	{
		joined_str[i] = s2[x];
		i++;
		x++;
	}
	joined_str[i] = '\0';
	return (joined_str);
}
