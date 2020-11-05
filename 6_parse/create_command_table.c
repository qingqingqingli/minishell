/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_command_table.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:00:03 by roybakker     #+#    #+#                 */
/*   Updated: 2020/10/29 10:42:36 by rbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		parse_command(t_data *data, char **envp)
{
	int ret;

	ret = 0;
	if (!data->envp)
		save_environment_variables(data, envp);
	ret = get_next_line(0, &data->input);
	if (ret == -1)
	{
		g_exit_code = 1;
		return (-1);
	}
	else if (ret == 0)
	{
		clear_memory(data);
		print(data, 2, "exit\n", 0);
		exit(0);
	}
	if (input_validation(data) == -1)
		return (-1);
	create_command_table(data, data->input, 0);
	return (0);
}

int		save_environment_variables(t_data *data, char **envp)
{
	int		index;
	int		envp_size;
	char	**malloced_envp;

	index = 0;
	envp_size = get_array_size(envp);
	malloced_envp = (char**)malloc(sizeof(char*) * (envp_size + 1));
	if (malloced_envp == NULL)
		envp_malloc_error(data, 0);
	while (index < envp_size)
	{
		malloced_envp[index] = ft_strdup(envp[index]);
		if (malloced_envp[index] == NULL)
			envp_malloc_error(data, malloced_envp);
		index++;
	}
	malloced_envp[index] = 0;
	data->envp = malloced_envp;
	data->args = 0;
	return (0);
}

int		create_command_table(t_data *data, char *line, int cmd)
{
	char	**commands;

	data->command_nb = get_amount_of_commands(line, 0);
	data->commands = (t_command_table**)malloc(sizeof(t_command_table*) *
													(data->command_nb + 1));
	if (data->commands == NULL)
		malloc_error(data, 0);
	commands = save_commands(line, data->command_nb, 0, 0);
	if (commands == NULL)
		malloc_error(data, 0);
	while (cmd < data->command_nb)
	{
		if (save_single_command(data, commands, cmd) == -1)
		{
			data->commands[cmd + 1] = NULL;
			malloc_error(data, commands);
		}
		cmd++;
	}
	data->commands[cmd] = NULL;
	free_array(commands);
	return (0);
}

int		save_single_command(t_data *data, char **commands, int cmd)
{
	data->commands[cmd] = (t_command_table*)malloc(sizeof(t_command_table) * 1);
	if (data->commands[cmd] == NULL)
		return (-1);
	initialize_command(data, cmd);
	data->commands[cmd]->token_nb = get_amount_of_tokens(commands[cmd], 0, 0);
	data->commands[cmd]->tokens = (char**)malloc(sizeof(char*) *
									(data->commands[cmd]->token_nb + 1));
	if (data->commands[cmd]->tokens == NULL)
		return (-1);
	save_tokens(data, commands, commands[cmd], cmd);
	return (0);
}

void	save_tokens(t_data *data, char **array, char *command, int cmd)
{
	int start;
	int index;
	int spaces;
	int len;
	int c;

	c = 0;
	index = 0;
	len = 0;
	while (command[c] == ' ' && command[c] != '\0')
		c++;
	while (command[c] != '\0' && index < data->commands[cmd]->token_nb)
	{
		spaces = 0;
		start = begin_token(command, c, &spaces);
		len = len_token(command, start, 0, &spaces);
		data->commands[cmd]->tokens[index] = ft_substr(command, start, len);
		if (data->commands[cmd]->tokens[index] == NULL)
			malloc_error(data, array);
		c += len + spaces;
		index++;
	}
	data->commands[cmd]->tokens[index] = 0;
}
