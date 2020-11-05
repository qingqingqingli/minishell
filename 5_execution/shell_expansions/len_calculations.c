/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   len_calculations.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/05 21:08:41 by roybakker     #+#    #+#                 */
/*   Updated: 2020/10/27 22:52:58 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_quotes_len(char *token, int *i, int *len)
{
	(*i)++;
	while (token[(*i)] != '\'')
	{
		(*i)++;
		(*len)++;
	}
	(*i)++;
}

void	double_quotes_len(t_data *data, char *token, int *i, int *len)
{
	(*i)++;
	while (token[(*i)] != '\"')
	{
		if (token[(*i)] == '\\')
			(*len) += escape_len_double_quotes(token, i, 0);
		else if (token[(*i)] == '$')
		{
			if (data->current_token[(*i) + 1] == '?')
				(*len) += exit_code_len(data, 0);
			else
				(*len) += env_var_len(data, token, (*i), 0);
			(*i)++;
			(*i) += token_var_len(token, (*i));
		}
		else
		{
			(*i)++;
			(*len)++;
		}
	}
	(*i)++;
}

int		escape_len_double_quotes(char *token, int *i, int len)
{
	(*i)++;
	if (token[(*i)] == '$' || token[(*i)] == '`' || \
		token[(*i)] == '\"' || token[(*i)] == '\\')
		len = 1;
	else
		len = 2;
	(*i)++;
	return (len);
}

int		env_var_len(t_data *data, char *token, int i, int len)
{
	char	*variable;
	int		var_len;
	int		x;

	i++;
	var_len = token_var_len(token, i);
	variable = ft_substr(token, i, var_len);
	if (variable == NULL)
		malloc_error(data, 0);
	x = 0;
	while (x < get_array_size(data->envp))
	{
		if (ft_strncmp(data->envp[x], variable, ft_strlen(variable)) == 0
							&& data->envp[x][ft_strlen(variable)] == '=')
		{
			len = ft_strlen(data->envp[x]) - ft_strlen(variable) - 1;
			free(variable);
			return (len);
		}
		x++;
	}
	free(variable);
	return (len);
}

int		exit_code_len(t_data *data, int len)
{
	char *exit_code;

	exit_code = ft_itoa(g_exit_code);
	if (exit_code == NULL)
		malloc_error(data, 0);
	len = ft_strlen(exit_code);
	free(exit_code);
	return (len);
}
