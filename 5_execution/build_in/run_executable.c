/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_executable.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 20:12:02 by qli           #+#    #+#                 */
/*   Updated: 2020/11/03 13:38:51 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_executable(t_data *data, int cmd, int tkn)
{
	char		*value;
	struct stat stats;

	value = data->commands[cmd]->tokens[tkn];
	if (value[0] == '\0')
	{
		close(data->iostream[READ]);
		close(data->iostream[WRITE]);
		clear_memory(data);
		exit(0);
	}
	else
		create_args(data, cmd, tkn, 1);
	if (data->args[0] == NULL || stat(data->args[0], &stats) == -1)
		print_special_errno(data, value, "command not found", 127);
	execve(data->args[0], data->args, data->envp);
	clear_memory(data);
	exit(1);
}
