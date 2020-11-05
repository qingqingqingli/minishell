/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/05 10:19:20 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 11:58:25 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_error(t_data *data, char **malloced_array)
{
	g_exit_code = 1;
	print(data, 2, "minishell : error due to malloc failure\n", 0);
	free_array(malloced_array);
	clear_memory(data);
	exit(1);
}

void	envp_malloc_error(t_data *data, char **failed_envp)
{
	if (failed_envp)
		free_array(failed_envp);
	print(data, 2, "minishell : error due to malloc failure\n", 0);
	exit(1);
}
