/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_pipe_fds.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qli <qli@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:50:30 by qli           #+#    #+#                 */
/*   Updated: 2020/10/20 08:38:07 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_not_used_fds(t_data *data, int cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->commands[cmd]->pipe_nb == 0)
		return ;
	while (i < data->commands[cmd]->pipe_nb)
	{
		j = 0;
		while (j < 2)
		{
			if (data->commands[cmd]->pipes[i][j] != data->iostream[READ] \
			&& data->commands[cmd]->pipes[i][j] != data->iostream[WRITE])
			{
				close(data->commands[cmd]->pipes[i][j]);
			}
			j++;
		}
		i++;
	}
}

void	close_used_fds(t_data *data, int cmd)
{
	if (data->commands[cmd]->pipe_nb == 0)
		return ;
	if (data->iostream[READ] != STDIN)
		close(data->iostream[READ]);
	if (data->iostream[WRITE] != STDOUT)
		close(data->iostream[WRITE]);
}

void	close_all_fds(t_data *data, int cmd)
{
	int	i;

	i = 0;
	while (i < data->commands[cmd]->pipe_nb)
	{
		close(data->commands[cmd]->pipes[i][READ]);
		close(data->commands[cmd]->pipes[i][WRITE]);
		i++;
	}
}
