/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/05 21:11:22 by roybakker     #+#    #+#                 */
/*   Updated: 2020/10/28 11:04:20 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_quotes(t_data *data, char **new_token, int *i, int *x)
{
	char *token;

	token = data->current_token;
	(*i)++;
	while (token[(*i)] != '\'')
	{
		(*new_token)[(*x)] = token[(*i)];
		(*x)++;
		(*i)++;
	}
	(*i)++;
}

void	double_quotes(t_data *data, char **new_token, int *i, int *x)
{
	(*i)++;
	while ((*x) < expansion_len(data, 0, 0))
	{
		if (data->current_token[(*i)] == '\\' && data->current_token[(*i)])
			escape_double_quotes(data, new_token, i, x);
		else if (data->current_token[(*i)] == '$')
		{
			if (data->current_token[(*i) + 1] == '?')
				exit_code(data, new_token, x);
			else
				env_variable(data, new_token, (*i), x);
			(*i)++;
			(*i) += token_var_len(data->current_token, (*i));
		}
		else
		{
			if (data->current_token[(*i)] == '\"')
				break ;
			(*new_token)[(*x)] = data->current_token[(*i)];
			(*x)++;
			(*i)++;
		}
	}
	(*i)++;
}

void	escape_double_quotes(t_data *data, char **new_token, int *i, int *x)
{
	char *token;

	token = data->current_token;
	(*i)++;
	if (token[(*i)] == '$' || token[(*i)] == '`' || \
		token[(*i)] == '\"' || token[(*i)] == '\\')
		(*new_token)[(*x)] = token[(*i)];
	else
	{
		(*new_token)[(*x)] = '\\';
		(*x)++;
		(*new_token)[(*x)] = token[(*i)];
	}
	(*x)++;
	(*i)++;
}

void	env_variable(t_data *data, char **new_token, int i, int *x)
{
	char	*token;
	int		var_len;
	char	*variable;
	int		z;

	i++;
	var_len = 0;
	token = data->current_token;
	var_len = token_var_len(token, i);
	variable = ft_substr(token, i, var_len);
	if (variable == NULL)
		malloc_error(data, 0);
	z = 0;
	while (z < get_array_size(data->envp))
	{
		if (ft_strncmp(data->envp[z], variable, ft_strlen(variable)) == 0
							&& data->envp[z][ft_strlen(variable)] == '=')
		{
			save_env_variable(data->envp[z], new_token, x);
			break ;
		}
		z++;
	}
	free(variable);
}

void	save_env_variable(char *variable, char **new_token, int *x)
{
	int i;

	i = 0;
	while (variable[i - 1] != '=')
		i++;
	while (variable[i] != '\0')
	{
		(*new_token)[(*x)] = variable[i];
		(*x)++;
		i++;
	}
}
