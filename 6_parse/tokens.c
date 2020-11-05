/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 13:23:47 by roybakker     #+#    #+#                 */
/*   Updated: 2020/10/31 15:22:57 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		begin_token(char *command, int cmd, int *spaces)
{
	while (ft_isspace(command[cmd]) == 1 && command[cmd] != '\0')
	{
		cmd++;
		(*spaces)++;
	}
	return (cmd);
}

int		len_token(char *command, int start, int len, int *spaces)
{
	int current_char;

	while (command[start + len] != '\0')
	{
		current_char = char_type(command[start + len]);
		if (current_char == meta_char)
		{
			meta_char_len(command, start, &len, &current_char);
			if (current_char == space)
				(*spaces)++;
			break ;
		}
		else if (current_char == normal_char)
			non_quoted_len(command, start, &len, &current_char);
		else if (current_char == double_quote || current_char == single_quote)
			quoted_len(command, start, &len, &current_char);
		if (current_char == meta_char)
			break ;
		if (current_char == space)
		{
			(*spaces)++;
			break ;
		}
	}
	return (len);
}

void	meta_char_len(char *command, int start, int *len, int *current_char)
{
	(*len) = (command[start + (*len)] == '>' &&
								command[start + (*len) + 1] == '>') ? 2 : 1;
	*current_char = char_type(command[start + (*len)]);
}

void	non_quoted_len(char *command, int start, int *len, int *current_char)
{
	while ((*current_char) == normal_char && command[start + (*len)] != '\0')
	{
		if (command[start + (*len)] == '\\')
			(*len) += 2;
		else
			(*len)++;
		*current_char = char_type(command[start + (*len)]);
	}
}

void	quoted_len(char *command, int start, int *len, int *current_char)
{
	int quotes;
	int	quote_type;

	quotes = 1;
	quote_type = (*current_char);
	(*len)++;
	*current_char = char_type(command[start + (*len)]);
	while (quotes != 0 && command[start + (*len)] != '\0')
	{
		if ((*current_char) == quote_type)
			quotes--;
		if (command[start + (*len)] == '\\' && quote_type != single_quote)
			(*len) += 2;
		else
			(*len)++;
		*current_char = char_type(command[start + (*len)]);
	}
}
