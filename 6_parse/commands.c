/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: roybakker <roybakker@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 13:23:31 by roybakker     #+#    #+#                 */
/*   Updated: 2020/10/28 19:41:57 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**save_commands(char *line, char command_nb, int i, int index)
{
	char	**commands;
	int		len;

	commands = (char**)malloc(sizeof(char*) * (command_nb + 1));
	if (commands == NULL)
		return (0);
	while (line[i] != '\0' && index < command_nb)
	{
		len = len_command(line, i, 0);
		if (check_for_empty_command(line, i) == 0)
		{
			commands[index] = ft_substr(line, i, len);
			if (commands[index] == NULL)
			{
				free_array(commands);
				return (0);
			}
			index++;
		}
		i += len;
		if (line[i] != '\0')
			i++;
	}
	commands[index] = 0;
	return (commands);
}

int		len_command(char *line, int i, int len)
{
	while (line[i + len] != '\0' && line[i + len] != ';')
	{
		if (char_type(line[i + len]) == single_quote ||
			char_type(line[i + len]) == double_quote)
			process_quotes(line + i, &len);
		(line[i + len] == '\\') ? len += 2 : len++;
	}
	return (len);
}

int		check_for_empty_command(char *line, int i)
{
	while (line[i] != ';' && line[i] != '\0')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	initialize_command(t_data *data, int cmd)
{
	data->commands[cmd]->pipes = NULL;
	data->commands[cmd]->tokens = NULL;
	data->commands[cmd]->pipe_nb = 0;
}
