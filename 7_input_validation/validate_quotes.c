/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 14:49:19 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/31 15:14:32 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		validate_single_quotes(t_data *data, char *character)
{
	int i;

	i = 0;
	(*character) = '\'';
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '\'')
		{
			i++;
			while (data->input[i] != '\'' && data->input[i] != '\0')
				i++;
			if (data->input[i] == '\0')
				return (-1);
			i++;
		}
		else
			(data->input[i] == '\\') ? i += 2 : i++;
	}
	return (0);
}

int		validate_double_quotes(t_data *data, char *character)
{
	int i;

	i = 0;
	(*character) = '\"';
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '\"')
		{
			(data->input[i] == '\\') ? i += 2 : i++;
			while (data->input[i] != '\"')
			{
				if (data->input[i] == '\0')
					return (-1);
				(data->input[i] == '\\') ? i += 2 : i++;
			}
		}
		(data->input[i] == '\\') ? i += 2 : i++;
	}
	return (0);
}
