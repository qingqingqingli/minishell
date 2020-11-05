/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_expansions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qli <qli@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:48:12 by qli           #+#    #+#                 */
/*   Updated: 2020/11/02 10:51:30 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_token_list(t_data *data, int cmd, int tkn, char *new_token)
{
	char	**env_var;
	int		array_size;
	char	**token_list;

	array_size = 0;
	if (data->commands[cmd]->tokens[tkn][0] == '$')
	{
		env_var = ft_split(new_token, ' ');
		if (env_var == NULL)
			malloc_error(data, &new_token);
		array_size = get_array_size(env_var);
		if (array_size > 1)
		{
			data->commands[cmd]->token_nb += array_size - 1;
			token_list = split_env_token(data, cmd, tkn, env_var);
			free_array(env_var);
			if (token_list == 0)
				malloc_error(data, &new_token);
			data->commands[cmd]->tokens = token_list;
			return ;
		}
		free_array(env_var);
	}
	free(data->commands[cmd]->tokens[tkn]);
	data->commands[cmd]->tokens[tkn] = new_token;
}

char	**split_env_token(t_data *data, int cmd, int tkn, char **env_var)
{
	char	**token_list;
	int		ret;
	int		i;

	i = 0;
	token_list = malloc(sizeof(char*) * (data->commands[cmd]->token_nb + 1));
	if (token_list == NULL)
		return (0);
	while (i < data->commands[cmd]->token_nb)
	{
		if (i < tkn)
			ret = copy_env_token(data->commands[cmd]->tokens[i],
			&token_list[i], token_list);
		else if (i < get_array_size(env_var) + tkn)
			ret = copy_env_token(env_var[i - tkn], &token_list[i], token_list);
		else
			ret = copy_env_token(data->commands[cmd]->tokens \
			[i - get_array_size(env_var) + 1], &token_list[i], token_list);
		if (ret == -1)
			return (0);
		i++;
	}
	token_list[i] = NULL;
	free_array(data->commands[cmd]->tokens);
	return (token_list);
}
