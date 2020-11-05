/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arguments_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 11:15:58 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/30 11:20:32 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		update_token_list(t_data *data, int cmd, int *tkn, int i)
{
	int		usable_tokens;
	char	**tokens;

	usable_tokens = count_usable_tokens(data, cmd, (*tkn));
	tokens = malloc(sizeof(char*) * (usable_tokens + 1));
	if (tokens == NULL)
		malloc_error(data, 0);
	while (i < usable_tokens)
	{
		if (check_token_usability(data->commands[cmd]->tokens,
									(*tkn)) == -1)
			(*tkn) += 2;
		else if (save_list_element(data->commands[cmd]->tokens[(*tkn)],
									&tokens[i], tkn, &i) == -1)
			malloc_error(data, tokens);
	}
	tokens[i] = 0;
	free_array(data->commands[cmd]->tokens);
	data->commands[cmd]->tokens = tokens;
	data->commands[cmd]->token_nb = usable_tokens;
	(*tkn) = 0;
	return (usable_tokens);
}

int		save_list_element(char *old_token, char **new_token, int *tkn, int *x)
{
	(*new_token) = ft_strdup(old_token);
	if ((*new_token) == NULL)
		return (-1);
	(*tkn)++;
	(*x)++;
	return (0);
}

int		count_usable_tokens(t_data *data, int cmd, int tkn)
{
	int		amount;

	amount = 0;
	while (tkn < data->commands[cmd]->token_nb)
	{
		if (data->commands[cmd]->tokens[tkn][0] == '|')
			break ;
		else if (redirection(data->commands[cmd]->tokens[tkn]) > piped)
			tkn += 2;
		else
		{
			tkn++;
			amount++;
		}
	}
	while (tkn < data->commands[cmd]->token_nb)
	{
		tkn++;
		amount++;
	}
	return (amount);
}

int		get_start_point(t_data *data, int cmd, int *tkn)
{
	char	*token;
	int		i;

	i = (*tkn);
	token = data->commands[cmd]->tokens[i];
	while (token != NULL && token[0] != '|')
	{
		i++;
		token = data->commands[cmd]->tokens[i];
	}
	if (token == NULL)
		return (0);
	i++;
	(*tkn) += i;
	return (i);
}
