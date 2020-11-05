/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_loop.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 16:36:24 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/03 16:34:20 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution_loop(t_data *data, int cmd, int tkn)
{
	while (cmd < data->command_nb)
	{
		set_dollar_sign_value(data, cmd);
		initialize_pipes(data, cmd);
		tkn = 0;
		while (tkn < data->commands[cmd]->token_nb)
		{
			if (set_iostream(data, cmd, &tkn) != -1)
			{
				if (!data->commands[cmd]->pipe_nb && custom_cmd(data, cmd, tkn))
					execute_command(data, cmd, tkn);
				else
					fork_command(data, cmd, tkn);
			}
			close_used_fds(data, cmd);
			update_token_position(data, cmd, &tkn);
			data->commands[cmd]->pipe_pos++;
		}
		close_all_fds(data, cmd);
		wait_for_child_process();
		cmd++;
	}
	clear_used_memory(data);
}

void	fork_command(t_data *data, int cmd, int tkn)
{
	g_pid = fork();
	if (g_pid == -1)
		exit(1);
	if (g_pid == 0)
	{
		close_not_used_fds(data, cmd);
		if (dup2(data->iostream[READ], STDIN) == -1)
			exit(1);
		if (dup2(data->iostream[WRITE], STDOUT) == -1)
			exit(1);
		execute_command(data, cmd, tkn);
		clear_memory(data);
		exit(0);
	}
}

void	wait_for_child_process(void)
{
	int status;

	while (wait(&status) > 0)
	{
		if (g_exit_code == 2 || g_exit_code == 3)
			g_exit_code = 128 + g_exit_code;
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (WCOREDUMP(status) > 0)
			g_exit_code = 1;
		if (WIFSTOPPED(status))
			g_exit_code = WSTOPSIG(status);
	}
}

void	execute_command(t_data *data, int cmd, int tkn)
{
	char	*value;

	preform_shell_expansions(data, cmd, 0);
	g_exit_code = 0;
	skip_empty_token(data, cmd, &tkn);
	value = data->commands[cmd]->tokens[tkn];
	if (compare_command("echo", value, 4) == 0)
		execute_echo(data, cmd, tkn, 0);
	else if (compare_command("cd", value, 2) == 0)
		execute_cd(data, cmd, tkn, 0);
	else if (compare_command("pwd", value, 3) == 0)
		execute_pwd(data, cmd);
	else if (compare_command("export", value, 6) == 0)
		execute_export(data, cmd, tkn);
	else if (compare_command("unset", value, 5) == 0)
		execute_unset(data, cmd, tkn, 0);
	else if (compare_command("env", value, 3) == 0)
		execute_env(data, cmd, tkn, 0);
	else if (compare_command("exit", value, 4) == 0)
		execute_exit(data, cmd, tkn, 0);
	else
		run_executable(data, cmd, tkn);
}
