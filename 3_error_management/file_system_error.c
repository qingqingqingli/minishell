/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_system_error.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/05 10:18:54 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/02 11:21:04 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_file_permission(t_data *data, char *path)
{
	struct stat stats;

	if (stat(path, &stats) == -1)
	{
		free(data->args);
		data->args = NULL;
		print_builtin_errno(data, path, 127);
	}
	if ((stats.st_mode & S_IFDIR) == 16384)
		print_special_errno(data, path, "is a directory", 126);
	if ((stats.st_mode & S_IXUSR) == 0)
		print_special_errno(data, path, "Permission denied", 126);
}

void	print_redir_erno(t_data *data, char *filename, int exit_code)
{
	int errno;

	print(data, 2, "minishell : ", 0);
	print(data, 2, filename, 0);
	print(data, 2, " : ", 0);
	print(data, 2, strerror(errno), 0);
	print_char(data, 2, '\n', 0);
	g_exit_code = exit_code;
}

void	print_errno(t_data *data, int cmd, char *filename, int exit_code)
{
	int errno;

	print(data, 2, "minishell : ", 0);
	print(data, 2, filename, 0);
	print(data, 2, " : ", 0);
	print(data, 2, strerror(errno), 0);
	print_char(data, 2, '\n', 0);
	if (data->commands[cmd]->pipe_nb == 0)
		g_exit_code = exit_code;
	else
	{
		clear_memory(data);
		exit(exit_code);
	}
}

void	print_builtin_errno(t_data *data, char *filename, int exit_code)
{
	int errno;

	print(data, 2, "minishell : ", 0);
	print(data, 2, filename, 0);
	print(data, 2, " : ", 0);
	print(data, 2, strerror(errno), 0);
	print_char(data, 2, '\n', 0);
	clear_memory(data);
	exit(exit_code);
}

void	get_directory_error(t_data *data)
{
	print(data, 2, "minishell : getcwd function failed\n", 0);
	clear_used_memory(data);
	exit(1);
}
