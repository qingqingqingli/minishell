/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_six.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 13:11:44 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/30 10:43:55 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		compare_command(char *command, char *token_command, int len)
{
	int token_len;

	token_len = ft_strlen(token_command);
	if (token_len != len)
		return (-1);
	return (ft_strncmp(command, token_command, len));
}

int		check_token_usability(char **tokens, int i)
{
	int x;

	x = i;
	while (x > 0)
	{
		if (tokens[x][0] == '|')
			return (0);
		x--;
	}
	if (compare_command("<", tokens[i], 1) == 0 ||
		compare_command(">", tokens[i], 1) == 0 ||
		compare_command(">>", tokens[i], 2) == 0)
		return (-1);
	else
		return (0);
}

int		calculate_needed_tokens(t_data *data, int cmd, int tkn)
{
	int		count;
	char	*value;

	count = 0;
	value = data->commands[cmd]->tokens[tkn];
	while (value != NULL && value[0] != '|')
	{
		if (ft_strncmp("\\|", value, 2) == 0)
		{
			free(data->commands[cmd]->tokens[tkn]);
			data->commands[cmd]->tokens[tkn] = ft_strdup("|");
			if (data->commands[cmd]->tokens[tkn] == NULL)
				malloc_error(data, 0);
		}
		count++;
		tkn++;
		value = data->commands[cmd]->tokens[tkn];
		if (value == NULL)
			break ;
	}
	data->used_tokens = count;
	return (count);
}

void	update_token_position(t_data *data, int cmd, int *tkn)
{
	char	*value;

	if (data->used_tokens == 0)
		calculate_needed_tokens(data, cmd, (*tkn));
	(*tkn) += data->used_tokens;
	data->used_tokens = 0;
	value = data->commands[cmd]->tokens[(*tkn)];
	if (value == NULL)
		return ;
	else if (data->commands[cmd]->tokens[(*tkn)][0] == '|')
		(*tkn)++;
	copy_remaining_tokens(data, cmd, (*tkn));
	(*tkn) = 0;
}

void	copy_remaining_tokens(t_data *data, int cmd, int tkn)
{
	char	**token_list;
	int		size;

	size = tkn;
	while (data->commands[cmd]->tokens[size] != NULL)
		size++;
	size -= tkn;
	data->commands[cmd]->token_nb = size;
	token_list = malloc(sizeof(char *) * (size + 1));
	if (token_list == NULL)
		malloc_error(data, 0);
	size = 0;
	while (data->commands[cmd]->tokens[tkn] != NULL)
	{
		token_list[size] = ft_strdup(data->commands[cmd]->tokens[tkn]);
		if (token_list[size] == NULL)
			malloc_error(data, token_list);
		size++;
		tkn++;
	}
	token_list[size] = NULL;
	free_array(data->commands[cmd]->tokens);
	data->commands[cmd]->tokens = token_list;
}
