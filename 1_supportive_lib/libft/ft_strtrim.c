/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 08:45:07 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/22 16:08:44 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		start(char const *s1, char const *set)
{
	int i;
	int x;
	int count;

	i = 0;
	while (s1[i] != '\0')
	{
		x = 0;
		count = 0;
		while (set[x] != '\0')
		{
			if (s1[i] == set[x])
				count++;
			x++;
		}
		if (count == 0)
			return (i);
		i++;
	}
	if (s1[0] == set[0])
		return (-1);
	return (0);
}

static int		end(char const *s1, char const *set)
{
	int i;
	int x;
	int count;
	int end;

	end = 0;
	i = (ft_strlen(s1) - 1);
	while (i > 0)
	{
		x = 0;
		count = 0;
		while (set[x] != '\0')
		{
			if (s1[i] == set[x])
				count++;
			x++;
		}
		if (count == 0)
			return (end);
		i--;
		end++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char*trimmed_string;
	int size;
	int i;
	int x;

	if (s1 == 0)
		return (0);
	i = 0;
	x = start(s1, set);
	size = (ft_strlen(s1) - start(s1, set) - end(s1, set));
	if (start(s1, set) == -1)
		return (ft_strdup(""));
	trimmed_string = malloc(sizeof(char) * (size + 1));
	if (!trimmed_string)
		return (0);
	while (i < size)
	{
		trimmed_string[i] = s1[x];
		x++;
		i++;
	}
	trimmed_string[i] = '\0';
	return (trimmed_string);
}
