/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: roybakker <roybakker@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 14:51:19 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 14:51:13 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_env(t_data *data, int cmd, int tkn, int needed_tokens)
{
	int index;

	index = 0;
	needed_tokens = calculate_needed_tokens(data, cmd, tkn);
	if (validate_args(data, cmd, &tkn, needed_tokens))
	{
		print(data, 2, "minishell : env : No such file or directory\n", 0);
		g_exit_code = 1;
		return ;
	}
	if (compare_command("env", data->commands[cmd]->tokens[tkn], 3) != 0)
	{
		if (check_args(data, cmd, tkn, needed_tokens))
			return ;
	}
	else
		while (data->envp[index] != 0)
		{
			if (env_with_value(data->envp[index]))
			{
				print(data, data->iostream[1], data->envp[index], 0);
				print_char(data, data->iostream[1], '\n', 0);
			}
			index++;
		}
}

int		check_args(t_data *data, int cmd, int tkn, int needed_tokens)
{
	char		*path;
	struct stat stats;

	while (tkn < needed_tokens)
	{
		path = data->commands[cmd]->tokens[tkn];
		if (stat(path, &stats) == -1)
		{
			print_errno(data, cmd, path, 1);
			g_exit_code = 1;
			return (1);
		}
		if ((stats.st_mode & S_IXUSR) == 0)
		{
			print(data, 2, "minishell : ", 0);
			print(data, 2, path, 0);
			print(data, 2, " : ", 0);
			print(data, 2, "Permission denied", 0);
			print_char(data, 2, '\n', 0);
			g_exit_code = 126;
			return (1);
		}
		tkn++;
	}
	return (0);
}

int		env_with_value(char *variable)
{
	int i;

	i = 0;
	while (variable[i] != '\0')
	{
		if (variable[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
