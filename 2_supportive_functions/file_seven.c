/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_seven.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:10:21 by rbakker       #+#    #+#                 */
/*   Updated: 2020/11/03 10:10:56 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		command_check(char check_value, char charachter)
{
	if (charachter == check_value || charachter == '|' || charachter == ';' ||
		charachter == '\0')
		return (-1);
	else
		return (0);
}

int		redirection_check(char *str)
{
	if (!str)
		return (0);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (redirected);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (redirected);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (redirected);
	return (0);
}

int		quotes_check(char *str)
{
	if (str[0] == '\"')
		return (double_quote);
	else if (str[0] == '\'')
		return (single_quote);
	else
		return (normal_char);
}

int		validate_export_token(t_data *data, int cmd, int tkn)
{
	char	*value;
	int		i;

	i = 0;
	value = data->commands[cmd]->tokens[tkn];
	while (ft_isalpha(value[i]) || value[i] == '_' || ft_isdigit(value[i]))
		i++;
	if (ft_isdigit(value[0]) || value[0] == '=' ||
		(value[i] != '=' && value[i] != '\0'))
	{
		print_unset_error(data, value);
		return (0);
	}
	return (1);
}

int		envp_with_value(char *token)
{
	int i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
