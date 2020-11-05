/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_arguments.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qli <qli@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 15:05:59 by qli           #+#    #+#                 */
/*   Updated: 2020/11/03 13:00:12 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_args(t_data *data, int cmd, int tkn, int x)
{
	int args_num;

	args_num = check_args_num(data, cmd, tkn);
	data->args = (char **)malloc(sizeof(char *) * (args_num + 1));
	if (data->args == NULL)
		malloc_error(data, 0);
	if (!check_relative_path(data->commands[cmd]->tokens[tkn]))
		data->args[0] = get_abs_path(data, cmd, tkn, 0);
	else
	{
		check_file_permission(data, data->commands[cmd]->tokens[tkn]);
		data->args[0] = ft_strdup(data->commands[cmd]->tokens[tkn]);
		if (data->args[0] == NULL)
			malloc_error(data, 0);
	}
	if (data->args[0])
		copy_valid_args(data, cmd, tkn, x);
}

int		check_args_num(t_data *data, int cmd, int tkn)
{
	int args_num;

	args_num = 0;
	while (tkn < data->commands[cmd]->token_nb)
	{
		if (ft_strncmp(data->commands[cmd]->tokens[tkn], ">", 1) == 0 || \
		ft_strncmp(data->commands[cmd]->tokens[tkn], "<", 1) == 0 || \
		ft_strncmp(data->commands[cmd]->tokens[tkn], "|", 1) == 0)
		{
			return (args_num);
		}
		if (data->commands[cmd]->tokens[tkn][0] == '\0')
			tkn++;
		else
		{
			tkn++;
			args_num++;
		}
	}
	return (args_num);
}

char	*get_abs_path(t_data *data, int cmd, int tkn, int x)
{
	char		**path;
	char		*path_token;
	char		*abs_path;

	abs_path = NULL;
	if (find_path(data) == NULL)
		return (create_executable(data, cmd, tkn, abs_path));
	path = ft_split(find_path(data), ':');
	if (path == NULL)
		malloc_error(data, 0);
	path_token = ft_strjoin("/", data->commands[cmd]->tokens[tkn]);
	if (path_token == NULL)
		malloc_error(data, path);
	while (path[x] != NULL)
	{
		abs_path = check_path_array(data, path, path_token, x);
		if (abs_path)
			return (abs_path);
		x++;
	}
	free(path_token);
	free_array(path);
	return (0);
}

char	*create_executable(t_data *data, int cmd, int tkn, char *abs_path)
{
	abs_path = ft_strjoin("./", data->commands[cmd]->tokens[tkn]);
	if (abs_path == NULL)
		malloc_error(data, 0);
	return (abs_path);
}

char	*check_path_array(t_data *data, char **path, char *path_token, int x)
{
	char		*abs_path;
	struct stat stats;

	abs_path = ft_strjoin(path[x], path_token);
	if (abs_path == NULL)
	{
		free(path_token);
		malloc_error(data, path);
	}
	if (stat(abs_path, &stats) == 0)
	{
		check_file_permission(data, abs_path);
		free(path_token);
		free_array(path);
		return (abs_path);
	}
	free(abs_path);
	return (0);
}
