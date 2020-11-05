/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_expansions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/05 19:44:06 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/02 10:28:37 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	preform_shell_expansions(t_data *data, int cmd, int tkn)
{
	int		len;
	char	*new_token;

	len = 0;
	while (tkn < data->commands[cmd]->token_nb)
	{
		data->current_token = data->commands[cmd]->tokens[tkn];
		len = expansion_len(data, 0, 0);
		new_token = malloc(sizeof(char) * (len + 1));
		if (new_token == NULL)
			malloc_error(data, 0);
		if (!empty_quotes(data, cmd, tkn, &new_token))
		{
			expand_token(data, &new_token, 0, 0);
			if (compare_command("echo", data->commands[cmd]->tokens[0], 4) != 0)
				expand_token_list(data, cmd, tkn, new_token);
			else
			{
				free(data->commands[cmd]->tokens[tkn]);
				data->commands[cmd]->tokens[tkn] = new_token;
			}
		}
		tkn++;
	}
}

int		empty_quotes(t_data *data, int cmd, int tkn, char **new_token)
{
	int i;

	i = 0;
	if (data->current_token[0] == '\"' || data->current_token[0] == '\'')
		while (data->current_token[i] == data->current_token[0])
			i++;
	if (!(i % 2) && i != 0)
	{
		free((*new_token));
		(*new_token) = malloc(sizeof(char) * 2);
		if (new_token == NULL)
			malloc_error(data, 0);
		(*new_token) = ft_strdup(" ");
		if (new_token[0] == NULL)
			malloc_error(data, new_token);
		free(data->commands[cmd]->tokens[tkn]);
		data->commands[cmd]->tokens[tkn] = (*new_token);
		return (1);
	}
	return (0);
}

int		expansion_len(t_data *data, int i, int len)
{
	while (data->current_token[i] != '\0')
	{
		if (data->current_token[i] == '\'')
			single_quotes_len(data->current_token, &i, &len);
		else if (data->current_token[i] == '\"')
			double_quotes_len(data, data->current_token, &i, &len);
		else if (data->current_token[i] == '$')
		{
			if (data->current_token[i + 1] == '?')
				len += exit_code_len(data, 0);
			else
				len += env_var_len(data, data->current_token, i, 0);
			i++;
			i += token_var_len(data->current_token, i);
		}
		else
		{
			i += (data->current_token[i] == '\\' &&
									data->current_token[i + 1] != '|') ? 2 : 1;
			len++;
		}
	}
	return (len);
}

void	expand_token(t_data *data, char **new_token, int i, int x)
{
	while (x < expansion_len(data, 0, 0))
	{
		if (data->current_token[i] == '\'')
			single_quotes(data, new_token, &i, &x);
		else if (data->current_token[i] == '\"')
			double_quotes(data, new_token, &i, &x);
		else if (data->current_token[i] == '$')
		{
			if (data->current_token[i + 1] == '?')
				exit_code(data, new_token, &x);
			else
				env_variable(data, new_token, i, &x);
			i++;
			i += token_var_len(data->current_token, i);
		}
		else
		{
			(data->current_token[i] == '\\' &&
								data->current_token[i + 1] != '|') ? i++ : i;
			(*new_token)[x] = data->current_token[i];
			x++;
			i++;
		}
	}
	(*new_token)[x] = '\0';
}

void	exit_code(t_data *data, char **new_token, int *x)
{
	char	*exit_code;
	int		i;

	i = 0;
	exit_code = ft_itoa(g_exit_code);
	if (exit_code == NULL)
		malloc_error(data, 0);
	while (exit_code[i] != '\0')
	{
		(*new_token)[(*x)] = exit_code[i];
		(*x)++;
		i++;
	}
	free(exit_code);
}
