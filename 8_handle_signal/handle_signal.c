/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_signal.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qli <qli@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/21 13:15:18 by qli           #+#    #+#                 */
/*   Updated: 2020/11/03 16:33:26 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(void)
{
	if (signal(SIGINT, &sigint_handler) == SIG_ERR)
		g_exit_code = 1;
	if (signal(SIGQUIT, &sigquit_handler) == SIG_ERR)
		g_exit_code = 1;
}

void	print_prompt(void)
{
	if (ft_printf("\n\033[1;32m→\033[1;36m %s\033[0m ", g_dir_path) == -1)
		g_exit_code = -1;
}

void	sigint_handler(int signum)
{
	g_exit_code = 2;
	if (g_pid == 0)
	{
		g_exit_code = 130;
		print_prompt();
	}
	else
	{
		if (!kill(g_pid, g_exit_code))
		{
			if (write(2, "\n", 1) == -1)
				g_exit_code = -1;
			g_pid = 0;
		}
		else
		{
			g_exit_code = 130;
			print_prompt();
		}
	}
	if (signal(signum, sigint_handler) == SIG_ERR)
		g_exit_code = 1;
}

void	sigquit_handler(int signum)
{
	g_exit_code = 3;
	if (g_pid == 0)
	{
		if (write(2, "\b\b  \b\b", 6) == -1)
			g_exit_code = -1;
		g_exit_code = 0;
	}
	else
	{
		if (!kill(g_pid, g_exit_code))
		{
			if (write(2, "Quit: 3\n", 8) == -1)
				g_exit_code = -1;
			g_pid = 0;
		}
		else
		{
			if (write(2, "\b\b  \b\b", 6) == -1)
				g_exit_code = -1;
			g_exit_code = 0;
		}
	}
	if (signal(signum, sigquit_handler) == SIG_ERR)
		g_exit_code = 1;
}
