/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_redirections.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 14:15:21 by roybakker     #+#    #+#                 */
/*   Updated: 2020/10/29 16:19:31 by rbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_file_name(t_data *data, int cmd, int tkn)
{
	int		len;
	char	*new_token;

	len = 0;
	data->current_token = data->commands[cmd]->tokens[tkn];
	len = expansion_len(data, 0, 0);
	new_token = malloc(sizeof(char) * (len + 1));
	if (new_token == NULL)
		malloc_error(data, 0);
	expand_token(data, &new_token, 0, 0);
	free(data->commands[cmd]->tokens[tkn]);
	data->commands[cmd]->tokens[tkn] = new_token;
}

void	create_output_file(t_data *data, int cmd, int *tkn, int *fd)
{
	char *filename;

	(*tkn)++;
	get_file_name(data, cmd, (*tkn));
	filename = data->commands[cmd]->tokens[(*tkn)];
	if ((*fd) != unused)
		close((*fd));
	if (redirection(data->commands[cmd]->tokens[(*tkn) - 1]) == overwrite)
		(*fd) = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		(*fd) = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if ((*fd) == -1)
		print_redir_erno(data, data->commands[cmd]->tokens[(*tkn)], 1);
}

void	create_input_file(t_data *data, int cmd, int *tkn, int *fd)
{
	char *filename;

	(*tkn)++;
	get_file_name(data, cmd, (*tkn));
	filename = data->commands[cmd]->tokens[(*tkn)];
	if ((*fd) != unused)
		close((*fd));
	(*fd) = open(filename, O_RDONLY);
	if ((*fd) == -1)
		print_redir_erno(data, data->commands[cmd]->tokens[(*tkn)], 1);
}
