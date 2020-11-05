/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 11:20:52 by qli           #+#    #+#                 */
/*   Updated: 2020/11/03 13:57:01 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_pwd(t_data *data, int cmd)
{
	char	buf[PATH_MAX];
	char	*value;

	value = getcwd(buf, (size_t)PATH_MAX);
	if (value == NULL)
		print_errno(data, cmd, "pwd", 1);
	print(data, data->iostream[1], value, 0);
	print_char(data, data->iostream[1], '\n', 0);
}
