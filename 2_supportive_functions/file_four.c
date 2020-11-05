/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_four.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/08 14:47:32 by roybakker     #+#    #+#                 */
/*   Updated: 2020/10/28 18:50:45 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		option(char *str)
{
	int result;

	result = ft_strncmp(str, "-n", 2);
	return (result);
}

int		check_relative_path(char *command)
{
	int i;

	i = 0;
	while (ft_isspace(command[i]) == 1)
		i++;
	if (command[i] == '/' || command[i] == '.')
		return (1);
	else
		return (0);
}

int		ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*find_path(t_data *data)
{
	int i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp("PATH", data->envp[i], 4) == 0)
			return (data->envp[i] + 5);
		i++;
	}
	return (NULL);
}

int		redirection(char *str)
{
	int result;

	result = 0;
	if (!str)
		return (0);
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		result = piped;
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		result = input;
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		result = overwrite;
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		result = append;
	return (result);
}
