/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_iostream.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 17:46:32 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/30 10:47:50 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		set_iostream(t_data *data, int cmd, int *tkn)
{
	data->iostream[READ] = 0;
	data->iostream[WRITE] = 1;
	if (data->commands[cmd]->pipe_nb > 0)
		set_pipe_fds(data, cmd);
	if (data->commands[cmd]->token_nb > 0)
	{
		if (set_redirection_fds(data, cmd, (*tkn)) == -1)
		{
			update_token_list(data, cmd, tkn, 0);
			g_exit_code = 1;
			return (-1);
		}
		if (!update_token_list(data, cmd, tkn, 0))
			return (-1);
	}
	return (0);
}

void	set_pipe_fds(t_data *data, int cmd)
{
	int pipe_pos;
	int	pipe_nb;

	pipe_pos = data->commands[cmd]->pipe_pos;
	pipe_nb = data->commands[cmd]->pipe_nb;
	if (pipe_pos == 0)
	{
		data->iostream[WRITE] = data->commands[cmd]->pipes[pipe_pos][STDOUT];
	}
	else if (pipe_pos < pipe_nb)
	{
		data->iostream[READ] = data->commands[cmd]->pipes[pipe_pos - 1][STDIN];
		data->iostream[WRITE] = data->commands[cmd]->pipes[pipe_pos][STDOUT];
	}
	else if (pipe_pos >= pipe_nb)
	{
		data->iostream[READ] = data->commands[cmd]->pipes[pipe_pos - 1][STDIN];
	}
}

int		set_redirection_fds(t_data *data, int cmd, int tkn)
{
	char	*value;
	int		fd[2];

	fd[READ] = unused;
	fd[WRITE] = unused;
	value = data->commands[cmd]->tokens[tkn];
	while (tkn < data->commands[cmd]->token_nb && fd[READ] != -1
													&& fd[WRITE] != -1)
	{
		if (redirection(value) == piped)
			break ;
		if (redirection(value) == overwrite || redirection(value) == append)
			create_output_file(data, cmd, &tkn, &fd[WRITE]);
		if (redirection(value) == input)
			create_input_file(data, cmd, &tkn, &fd[READ]);
		tkn++;
		value = data->commands[cmd]->tokens[tkn];
	}
	if (fd[READ] == -1 || fd[WRITE] == -1)
		return (-1);
	if (fd[READ] != unused)
		data->iostream[READ] = fd[READ];
	if (fd[WRITE] != unused)
		data->iostream[WRITE] = fd[WRITE];
	return (0);
}
