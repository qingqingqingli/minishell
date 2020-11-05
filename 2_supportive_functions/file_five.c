/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_five.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 16:44:49 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 12:59:55 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_array_size(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != 0)
		i++;
	return (i);
}

int		get_command_table_size(t_command_table **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != 0)
		i++;
	return (i);
}

int		token_var_len(char *str, int i)
{
	int len;

	len = 0;
	while (ft_isalpha(str[i + len]) == 1 || str[i + len] == '?' ||
			str[i + len] == '_' || ft_isdigit(str[i + len]) == 1)
		len++;
	return (len);
}

int		custom_cmd(t_data *data, int cmd, int tkn)
{
	char *value;

	value = data->commands[cmd]->tokens[tkn];
	if (compare_command("echo", value, 4) == 0 ||
		compare_command("cd", value, 2) == 0 ||
		compare_command("pwd", value, 3) == 0 ||
		compare_command("export", value, 6) == 0 ||
		compare_command("unset", value, 5) == 0 ||
		compare_command("env", value, 3) == 0 ||
		compare_command("exit", value, 4) == 0)
		return (1);
	else
		return (0);
}

void	copy_valid_args(t_data *data, int cmd, int tkn, int x)
{
	int args_num;

	args_num = check_args_num(data, cmd, tkn);
	while (x < args_num)
	{
		if (data->commands[cmd]->tokens[tkn + x][0] != '\0')
		{
			data->args[x] = ft_strdup(data->commands[cmd]->tokens[tkn + x]);
			if (data->args[x] == NULL)
				malloc_error(data, 0);
			x++;
		}
		else
			tkn++;
	}
	data->args[args_num] = NULL;
}
