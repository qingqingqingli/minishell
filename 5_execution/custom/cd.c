/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 14:50:20 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 13:33:20 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_cd(t_data *data, int cmd, int tkn, int needed_tokens)
{
	char	*value;

	needed_tokens = calculate_needed_tokens(data, cmd, tkn);
	if (validate_args(data, cmd, &tkn, needed_tokens))
		return (multiple_args(data));
	value = data->commands[cmd]->tokens[tkn];
	if (compare_command("~", value, 1) == 0 ||
		compare_command("cd", value, 2) == 0 ||
		ft_strncmp("~/", value, 2) == 0)
		go_to_home(data, cmd, value, needed_tokens);
	else if (chdir(value) == -1)
		print_errno(data, cmd, value, 1);
	free(g_dir_path);
	g_dir_path = get_current_directory(data);
}

void	multiple_args(t_data *data)
{
	print(data, 2, "minishell : cd : too many arguments\n", 0);
	g_exit_code = 1;
}

void	go_to_home(t_data *data, int cmd, char *value, int needed_tokens)
{
	char	*home_path;
	int		x;
	int		updated_home_path;

	x = 0;
	updated_home_path = 0;
	while (data->envp[x] != NULL)
	{
		if (ft_strncmp("HOME", data->envp[x], 4) == 0)
		{
			home_path = data->envp[x] + 5;
			break ;
		}
		x++;
	}
	if (needed_tokens > 1 && ft_strlen(value) > 2 &&
		ft_strncmp("~/", value, 2) == 0)
	{
		home_path = expand_home_path(data, value, home_path);
		updated_home_path = 1;
	}
	if (chdir(home_path) == -1)
		print_errno(data, cmd, home_path, 1);
	if (updated_home_path == 1)
		free(home_path);
}

char	*expand_home_path(t_data *data, char *value, char *home_path)
{
	char	*sub_path;
	char	*updated_home_path;

	sub_path = ft_substr(value, 1, ft_strlen(value) - 1);
	if (sub_path == NULL)
		malloc_error(data, 0);
	updated_home_path = ft_strjoin(home_path, sub_path);
	if (updated_home_path == NULL)
		malloc_error(data, &sub_path);
	free(sub_path);
	return (updated_home_path);
}
