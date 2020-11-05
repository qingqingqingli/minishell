/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 14:27:26 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/02 14:33:30 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define STDIN 0
# define READ 0
# define STDOUT 1
# define WRITE 1

/*
**--------------------------------GENERAL---------------------------------------
*/

extern	int				g_exit_code;
extern	char			*g_dir_path;
extern	int				g_pid;

typedef enum			e_defenitions
{
	unused = -2,
	space = 0,
	meta_char = 1,
	double_quote = 2,
	single_quote = 3,
	normal_char = 4,
	piped = 5,
	input = 6,
	overwrite = 7,
	append = 8,
	redirected = 9,
	succes = 10,
	save = 11
}						t_defenitions;

/*
**---------------------------------MINISHELL------------------------------------
*/

typedef struct			s_command_table
{
	char				**tokens;
	int					token_nb;
	int					**pipes;
	int					pipe_nb;
	int					pipe_pos;
}						t_command_table;

typedef struct			s_data
{
	int					iostream[2];
	char				*input;
	char				**envp;
	char				**args;
	t_command_table		**commands;
	int					command_nb;
	char				*current_token;
	int					used_tokens;
}						t_data;

#endif
