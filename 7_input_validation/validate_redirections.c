/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_redirections.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 14:50:47 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/23 13:24:39 by rbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		validate_input_redirection(t_data *data, char *character)
{
	int i;

	i = 0;
	(*character) = '<';
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '<')
		{
			i++;
			while (data->input[i] == ' ')
				i++;
			if (command_check('<', data->input[i]) == -1)
				return (-258);
		}
		else
			(data->input[i] == '\\') ? i += 2 : i++;
	}
	return (0);
}

int		validate_output_redirection(t_data *data, char *character)
{
	int i;

	i = 0;
	(*character) = '>';
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '>')
		{
			i++;
			if (data->input[i] == '>')
				i++;
			while (data->input[i] == ' ')
				i++;
			if (command_check('>', data->input[i]) == -1)
				return (-258);
		}
		else
			(data->input[i] == '\\') ? i += 2 : i++;
	}
	return (0);
}

int		validate_pipes(t_data *data, char *character)
{
	int i;

	i = 0;
	(*character) = '|';
	if (replace_double_pipes(data) == -1)
		return (-258);
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '|')
		{
			i++;
			while (data->input[i] == ' ')
				i++;
			if (command_check('|', data->input[i]) == -1)
				return (-258);
		}
		else
			(data->input[i] == '\\') ? i += 2 : i++;
	}
	return (0);
}

int		replace_double_pipes(t_data *data)
{
	int i;
	int	x;

	i = 0;
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '|' && data->input[i + 1] == '|')
		{
			x = 2;
			while (data->input[i + x] == ' ')
				x++;
			if (command_check('|', data->input[i + x]) == -1)
				return (-1);
			while (data->input[i + x] != ';' && data->input[i + x] != '\0')
				(data->input[i] == '\\') ? x += 2 : x++;
			reduce_input_str(data, x, &i);
		}
		else
			(data->input[i] == '\\') ? i += 2 : i++;
	}
	return (0);
}

void	reduce_input_str(t_data *data, int reduction, int *i)
{
	int		len;
	char	*new_str;
	int		x;
	int		y;

	x = 0;
	y = reduction;
	len = ft_strlen(data->input) - reduction;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		malloc_error(data, 0);
	while (data->input[x] != '|')
	{
		new_str[x] = data->input[x];
		x++;
	}
	while (data->input[x + y] != '\0')
	{
		new_str[x] = data->input[x + y];
		x++;
	}
	new_str[x] = '\0';
	free(data->input);
	data->input = new_str;
	(*i) = 0;
}
