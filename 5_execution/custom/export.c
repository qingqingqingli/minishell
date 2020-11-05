/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: roybakker <roybakker@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 14:50:36 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 12:50:40 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_export(t_data *data, int cmd, int tkn)
{
	int		needed_tokens;

	needed_tokens = calculate_needed_tokens(data, cmd, tkn);
	if (!check_multiple_args(data, cmd, tkn, needed_tokens))
		return (print_export_output(data, get_array_size(data->envp), 0, 0));
	tkn++;
	while (tkn < needed_tokens)
	{
		if (data->commands[cmd]->tokens[tkn][0] != '\0' &&
			validate_export_token(data, cmd, tkn))
		{
			if (unique_var(data, data->commands[cmd]->tokens[tkn]))
				add_var_envp(data, data->commands[cmd]->tokens[tkn]);
			else if (envp_with_value(data->commands[cmd]->tokens[tkn]))
				replace_var_envp(data, data->commands[cmd]->tokens[tkn]);
		}
		tkn++;
	}
}

void	add_var_envp(t_data *data, char *new_var)
{
	char	**new_envp;
	int		envp_size;
	int		index;

	index = 0;
	envp_size = get_array_size(data->envp);
	new_envp = (char**)malloc(sizeof(char*) * (envp_size + 2));
	if (new_envp == NULL)
		malloc_error(data, 0);
	while (index < envp_size)
	{
		new_envp[index] = ft_strdup(data->envp[index]);
		if (new_envp[index] == NULL)
			malloc_error(data, new_envp);
		index++;
	}
	new_envp[index] = ft_strdup(new_var);
	if (new_envp[index] == NULL)
		malloc_error(data, new_envp);
	new_envp[index + 1] = NULL;
	free_array(data->envp);
	data->envp = new_envp;
}

void	replace_var_envp(t_data *data, char *new_var)
{
	int	envp_size;
	int	i;

	i = 0;
	envp_size = get_array_size(data->envp);
	while (i < envp_size)
	{
		if (ft_strncmp(data->envp[i], new_var, token_var_len(new_var, 0)) == 0
			&& (data->envp[i][token_var_len(new_var, 0)] == '=' ||
				data->envp[i][token_var_len(new_var, 0)] == '\0'))
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(new_var);
			if (data->envp[i] == NULL)
			{
				free_incomplete_envp(data, i);
				malloc_error(data, 0);
			}
			return ;
		}
		i++;
	}
}
