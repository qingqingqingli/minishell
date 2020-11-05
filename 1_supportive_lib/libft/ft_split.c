/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 13:48:25 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/21 14:15:06 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		amount_words(char const *str, char c)
{
	int i;
	int word_count;

	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c) && (str[i + 1] == c || str[i + 1] == '\0'))
			word_count++;
		i++;
	}
	return (word_count);
}

static int		word_lenght(char const *str, char c, int word_count)
{
	int i;
	int x;
	int position;

	position = 0;
	x = 0;
	i = 0;
	while (x < word_count)
	{
		i = 0;
		while (str[position] == c)
			position++;
		while ((str[position] != c) && (str[position] != '\0'))
		{
			i++;
			position++;
		}
		x++;
	}
	return (i);
}

static int		mem_allocation(char **array, char const *str, char c)
{
	int		count;
	int		i;

	count = 1;
	i = 0;
	while (i < amount_words(str, c))
	{
		array[i] = malloc(sizeof(char) * (word_lenght(str, c, count) + 1));
		if (!array[i])
		{
			while (i >= 0)
			{
				free(array[i]);
				i--;
			}
			free(array);
			return (0);
		}
		i++;
		count++;
	}
	return (1);
}

static char		**ft_fill(char const *str, char c, char **array)
{
	int i;
	int x;
	int y;

	x = 0;
	i = 0;
	while (x < amount_words(str, c))
	{
		while (str[i] == c)
			i++;
		y = 0;
		while (str[i] != c && str[i] != '\0')
		{
			array[x][y] = str[i];
			i++;
			y++;
		}
		array[x][y] = '\0';
		x++;
	}
	array[x] = 0;
	return (array);
}

char			**ft_split(char const *str, char c)
{
	char	**array;
	int		succes;

	if (!str)
		return (0);
	array = (char**)malloc(sizeof(char*) * (amount_words(str, c) + 1));
	if (!array)
		return (0);
	succes = mem_allocation(array, str, c);
	if (!succes)
		return (0);
	return (ft_fill(str, c, array));
}
