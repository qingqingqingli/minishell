/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 14:50:49 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 14:58:50 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_unset(t_data *data, int cmd, int tkn, int needed_tokens)
{
	int		matching_vars;
	int		envp_size;
	char	**new_envp;

	envp_size = get_array_size(data->envp);
	needed_tokens = calculate_needed_tokens(data, cmd, tkn);
	validate_unset_token(data, cmd, tkn, needed_tokens);
	matching_vars = nb_of_matching_var(data, cmd, tkn, needed_tokens);
	if (!matching_vars)
		return ;
	new_envp = (char**)malloc(sizeof(char*) * (envp_size - matching_vars + 1));
	if (new_envp == NULL)
		malloc_error(data, 0);
	copy_remaining_vars(data, new_envp, cmd, tkn);
	free_array(data->envp);
	data->envp = new_envp;
}

void	validate_unset_token(t_data *data, int cmd, int tkn, int needed_tokens)
{
	char	*value;
	int		i;

	while (tkn < needed_tokens)
	{
		i = 0;
		value = data->commands[cmd]->tokens[tkn];
		while (ft_isalpha(value[i]) || value[i] == '_' || ft_isdigit(value[i]))
			i++;
		if (ft_isdigit(value[0]) || value[i] != '\0')
			print_unset_error(data, value);
		tkn++;
	}
}

void	copy_remaining_vars(t_data *data, char **new_envp, int cmd, int tkn)
{
	int envp_size;
	int	needed_tokens;
	int i;
	int x;

	x = 0;
	i = 0;
	needed_tokens = calculate_needed_tokens(data, cmd, tkn);
	envp_size = get_array_size(data->envp) -
				nb_of_matching_var(data, cmd, tkn, needed_tokens);
	while (i < envp_size)
	{
		if (!compare_var(data, cmd, tkn, data->envp[i + x]))
		{
			new_envp[i] = ft_strdup(data->envp[i + x]);
			if (new_envp[i] == NULL)
				malloc_error(data, new_envp);
			i++;
		}
		else
			x++;
	}
	new_envp[i] = 0;
}

int		compare_var(t_data *data, int cmd, int tkn, char *envp_var)
{
	int		needed_tokens;
	int		envp_var_len;
	int		var_len;
	char	*var;

	needed_tokens = calculate_needed_tokens(data, cmd, tkn);
	tkn++;
	envp_var_len = 0;
	var_len = 0;
	var = data->commands[cmd]->tokens[tkn];
	while (envp_var[envp_var_len] != '=' && envp_var[envp_var_len] != '\0')
		envp_var_len++;
	while (var[var_len] != '=' && var[var_len] != '\0')
		var_len++;
	while (tkn < needed_tokens)
	{
		var = data->commands[cmd]->tokens[tkn];
		if (ft_strncmp(envp_var, var, envp_var_len) == 0 &&
			var_len == envp_var_len)
			return (1);
		tkn++;
	}
	return (0);
}

int		nb_of_matching_var(t_data *data, int cmd, int tkn, int needed_tokens)
{
	int		var_len;
	char	*var;
	int		count;
	int		i;

	count = 0;
	tkn++;
	while (tkn < needed_tokens)
	{
		var = data->commands[cmd]->tokens[tkn];
		var_len = token_var_len(var, 0);
		i = 0;
		while (i < get_array_size(data->envp))
		{
			if (ft_strncmp(data->envp[i], var, var_len) == 0 &&
			(data->envp[i][var_len] == '=' || data->envp[i][var_len] == '\0'))
				count++;
			i++;
		}
		tkn++;
	}
	return (count);
}
