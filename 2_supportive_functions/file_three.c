/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_three.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 14:39:39 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 10:16:14 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	meta_token(char *command, int *cmd, int *tkn)
{
	(*tkn)++;
	if (command[(*cmd)] == '>' && command[(*cmd) + 1] == '>')
		(*cmd) += 2;
	else
		(*cmd)++;
}

void	quoted_sentence(char *command, int *cmd, int quote_type)
{
	int quotes;

	quotes = 1;
	(*cmd)++;
	while (quotes != 0 && command[(*cmd)] != '\0')
	{
		if (char_type(command[(*cmd)]) == quote_type)
			quotes--;
		(command[(*cmd)] == '\\' && quote_type != single_quote) ? (*cmd) += 2 :
																(*cmd)++;
	}
}

void	normal_token(char *command, int *cmd, int *tkn)
{
	(*tkn)++;
	while (command[(*cmd)] != '\0' && command[(*cmd)] != ' ')
	{
		while (char_type(command[(*cmd)]) == normal_char &&
														command[(*cmd)] != '\0')
			(command[(*cmd)] == '\\') ? (*cmd) += 2 : (*cmd)++;
		if (char_type(command[(*cmd)]) == single_quote ||
			char_type(command[(*cmd)]) == double_quote)
			quoted_sentence(command, cmd, char_type(command[(*cmd)]));
		if (char_type(command[(*cmd)]) == meta_char)
			break ;
	}
}

void	set_dollar_sign_value(t_data *data, int cmd)
{
	int		i;

	i = 0;
	while (i < data->commands[cmd]->token_nb)
	{
		if (compare_command("|", data->commands[cmd]->tokens[i], 1) == 0)
			break ;
		i++;
	}
	while (i < data->commands[cmd]->token_nb)
	{
		if (compare_command("$?", data->commands[cmd]->tokens[i], 2) == 0)
		{
			free(data->commands[cmd]->tokens[i]);
			data->commands[cmd]->tokens[i] = ft_strdup("0");
			if (data->commands[cmd]->tokens[i] == NULL)
				malloc_error(data, 0);
		}
		i++;
	}
}

int		unique_var(t_data *data, char *var)
{
	int		envp_size;
	int		var_len;
	int		i;

	envp_size = get_array_size(data->envp);
	var_len = token_var_len(var, 0);
	i = 0;
	while (i < envp_size)
	{
		if (ft_strncmp(data->envp[i], var, var_len) == 0 &&
			(data->envp[i][var_len] == '=' || data->envp[i][var_len] == '\0'))
			return (0);
		i++;
	}
	return (1);
}
