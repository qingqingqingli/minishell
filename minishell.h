/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 15:55:06 by roybakker     #+#    #+#                 */
/*   Updated: 2020/11/03 16:54:59 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include "1_supportive_lib/libft/libft.h"
# include "1_supportive_lib/gnl/get_next_line.h"
# include "1_supportive_lib/ft_printf/ft_printf.h"
# include "structs.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

/*
**--FOLDER-----------------2_SUPPORTIVE__FUNCTIONS------------------------------
*/

/*
** file_one.c
*/
void	print(t_data *data, int fd, char *str, char *malloced_str);
void	print_char(t_data *data, int fd, char c, char *malloced_str);
int		prompt(t_data *data);
char	*get_current_directory(t_data *data);
int		validate_args(t_data *data, int cmd, int *tkn, int needed_tokens);

/*
** file_two.c
*/
int		get_amount_of_commands(char *line, int i);
void	process_quotes(char *line, int *i);
int		get_amount_of_tokens(char *command, int cmd, int tkn);
int		char_type(char c);
int		copy_env_token(char *old_str, char **new_str, char **token_list);

/*
** file_three.c
*/
void	meta_token(char *command, int *cmd, int *tkn);
void	quoted_sentence(char *command, int *cmd, int x);
void	normal_token(char *command, int *cmd, int *tkn);
void	set_dollar_sign_value(t_data *data, int cmd);
int		unique_var(t_data *data, char *var);

/*
** file_four.c
*/
int		option(char *str);
int		check_relative_path(char *command);
int		ft_isspace(int c);
char	*find_path(t_data *data);
int		redirection(char *str);

/*
** file_five.c
*/
int		get_array_size(char **array);
int		get_command_table_size(t_command_table **array);
int		token_var_len(char *str, int i);
int		custom_cmd(t_data *data, int cmd, int tkn);
void	copy_valid_args(t_data *data, int cmd, int tkn, int x);

/*
** file_six.c
*/
int		compare_command(char *command, char *token_command, int len);
int		check_token_usability(char **tokens, int i);
int		calculate_needed_tokens(t_data *data, int cmd, int tkn);
void	update_token_position(t_data *data, int cmd, int *tkn);
void	copy_remaining_tokens(t_data *data, int cmd, int tkn);

/*
** file_seven.c
*/
int		command_check(char check_value, char charachter);
int		redirection_check(char *str);
int		quotes_check(char *str);
int		envp_with_value(char *token);
int		validate_export_token(t_data *data, int cmd, int tkn);

/*
** file_eight.c
*/
void	print_export_output(t_data *data, int array_size, int i, int j);
int		find_smallest_envp(t_data *data, int array_size);
void	print_envp_line(t_data *data, char *line);
int		check_multiple_args(t_data *data, int cmd, int tkn, int needed_tokens);
void	skip_empty_token(t_data *data, int cmd, int *tkn);

/*
**--FOLDER---------------------3_ERROR_MANAGEMENT-------------------------------
*/

/*
** external_function_error.c
*/
void	fork_error(t_data *data, int cmd);
void	write_error(t_data *data, char *malloced_str);
void	print_unset_error(t_data *data, char *cmd);
void	print_special_errno(t_data *data, char *cmd, char *msg, int exit_code);

/*
** file_system_error.c
*/
void	get_directory_error(t_data *data);
void	print_redir_erno(t_data *data, char *filename, int exit_code);
void	print_errno(t_data *data, int cmd, char *filename, int exit_code);
void	print_builtin_errno(t_data *data, char *filename, int exit_code);
void	check_file_permission(t_data *data, char *path);

/*
** memory_error.c
*/
void	malloc_error(t_data *data, char **malloced_array);
void	envp_malloc_error(t_data *data, char **failed_envp);

/*
** validation_error.c
*/
void	validation_error(t_data *data, char character, int exit_code);

/*
**--FOLDER---------------------4_MEMORY_MANAGEMENT------------------------------
*/

/*
** memory_management.c
*/
void	initialize(t_data *data);
void	clear_memory(t_data *data);
void	clear_used_memory(t_data *data);
void	free_incomplete_envp(t_data *data, int i);

/*
** free_functions.c
*/
void	free_string(char *string);
void	free_array(char **array);
void	free_int_array(int **array);
void	free_command_table(t_data *data);

/*
**--FOLDER------------------------5_EXECUTION-----------------------------------
*/

/*
**--SUB_FOLDER---------------------BUILD_IN-----------------------------------
*/

/*
** create_arguments.c
*/
void	create_args(t_data *data, int cmd, int tkn, int x);
int		check_args_num(t_data *data, int cmd, int tkn);
char	*get_abs_path(t_data *data, int cmd, int tkn, int x);
char	*create_executable(t_data *data, int cmd, int tkn, char *abs_path);
char	*check_path_array(t_data *data, char **path, char *path_token, int x);

/*
** run_executable.c
*/
void	run_executable(t_data *data, int cmd, int tkn);

/*
**--SUB_FOLDER-----------------------CUSTOM-------------------------------------
*/

/*
** cd.c
*/
void	execute_cd(t_data *data, int cmd, int tkn, int needed_tokens);
void	multiple_args(t_data *data);
void	go_to_home(t_data *data, int cmd, char *value, int needed_tokens);
char	*expand_home_path(t_data *data, char *value, char *home_path);

/*
** echo.c
*/
void	execute_echo(t_data *data, int cmd, int tkn, int needed_tokens);
int		newline_option(t_data *data, int cmd, int *tkn);

/*
** env.c
*/
void	execute_env(t_data *data, int cmd, int tkn, int needed_tokens);
int		check_args(t_data *data, int cmd, int tkn, int needed_tokens);
int		env_with_value(char *variable);

/*
** exit.c
*/
void	execute_exit(t_data *data, int cmd, int tkn, int needed_tokens);
int		numeric_arg_check(t_data *data, int cmd, int tkn);
void	too_many_args(t_data *data, int cmd);
void	numeric_error(t_data *data, int cmd, int tkn);

/*
** export.c
*/
void	execute_export(t_data *data, int cmd, int tkn);
void	add_var_envp(t_data *data, char *new_var);
void	replace_var_envp(t_data *data, char *new_var);

/*
** pwd.c
*/
void	execute_pwd(t_data *data, int cmd);

/*
** unset.c
*/
void	execute_unset(t_data *data, int cmd, int tkn, int needed_tokens);
void	validate_unset_token(t_data *data, int cmd, int tkn, int needed_tokens);
void	copy_remaining_vars(t_data *data, char **new_envp, int cmd, int tkn);
int		compare_var(t_data *data, int cmd, int tkn, char *envp_var);
int		nb_of_matching_var(t_data *data, int cmd, int tkn, int needed_tokens);

/*
**--SUB_FOLDER-------------------HANDLE_FDS-------------------------------------
*/

/*
** set_iostream.c
*/
int		set_iostream(t_data *data, int cmd, int *tkn);
void	set_pipe_fds(t_data *data, int cmd);
int		set_redirection_fds(t_data *data, int cmd, int tkn);

/*
** initialize_redirections.c
*/
void	get_file_name(t_data *data, int cmd, int tkn);
void	create_output_file(t_data *data, int cmd, int *tkn, int *fd);
void	create_input_file(t_data *data, int cmd, int *tkn, int *fd);

/*
** initialize_pipes.c
*/
void	initialize_pipes(t_data *data, int cmd);
int		get_pipes_amount(t_data *data, int cmd, int i);

/*
** close_pipe_fds.c
*/
void	close_not_used_fds(t_data *data, int cmd);
void	close_used_fds(t_data *data, int cmd);
void	close_all_fds(t_data *data, int cmd);

/*
**--SUB_FOLDER-------------------SHELL_EXPANSIONS-------------------------------
*/

/*
** expand_functions.c
*/
void	single_quotes(t_data *data, char **new_token, int *i, int *x);
void	double_quotes(t_data *data, char **new_token, int *i, int *x);
void	escape_double_quotes(t_data *data, char **new_token, int *i, int *x);
void	env_variable(t_data *data, char **new_token, int i, int *x);
void	save_env_variable(char *variable, char **new_token, int *x);

/*
** len_calculations.c
*/
void	single_quotes_len(char *token, int *i, int *len);
void	double_quotes_len(t_data *data, char *token, int *i, int *len);
int		escape_len_double_quotes(char *token, int *i, int len);
int		env_var_len(t_data *data, char *token, int i, int len);
int		exit_code_len(t_data *data, int len);

/*
** shell_expansions.c
*/
void	preform_shell_expansions(t_data *data, int i, int tkn);
int		empty_quotes(t_data *data, int cmd, int tkn, char **new_token);
int		expansion_len(t_data *data, int i, int len);
void	expand_token(t_data *data, char **new_token, int i, int x);
void	exit_code(t_data *data, char **new_token, int *x);

/*
** env_expansions.c
*/
void	expand_token_list(t_data *data, int cmd, int tkn, char *new_token);
char	**split_env_token(t_data *data, int cmd, int tkn, char **env_var);

/*
**-----------------------
*/

/*
** arguments_list.c
*/
int		update_token_list(t_data *data, int cmd, int *tkn, int i);
int		save_list_element(char *old_token, char **new_token, int *tkn, int *x);
int		count_usable_tokens(t_data *data, int cmd, int tkn);
int		get_start_point(t_data *data, int cmd, int *tkn);

/*
** execution_loop.c
*/
void	execution_loop(t_data *data, int cmd, int tkn);
void	fork_command(t_data *data, int cmd, int tkn);
void	wait_for_child_process(void);
void	execute_command(t_data *data, int cmd, int tkn);

/*
**--FOLDER--------------------------6_PARSE-------------------------------------
*/

/*
** commands.c
*/
char	**save_commands(char *line, char command_nb, int i, int index);
int		len_command(char *line, int i, int len);
int		check_for_empty_command(char *line, int i);
void	initialize_command(t_data *data, int cmd);

/*
** create_command_table.c
*/
int		parse_command(t_data *data, char **envp);
int		save_environment_variables(t_data *data, char **envp);
int		create_command_table(t_data *data, char *line, int cmd);
int		save_single_command(t_data *data, char **commands, int cmd);
void	save_tokens(t_data *data, char **array, char *command, int cmd);

/*
** tokens.c
*/
int		begin_token(char *command, int cmd, int *space);
int		len_token(char *command, int start, int len, int *spaces);
void	meta_char_len(char *command, int start, int *len, int *current_char);
void	non_quoted_len(char *command, int start, int *len, int *current_char);
void	quoted_len(char *command, int start, int *len, int *current_char);

/*
**--FOLDER---------------------7_INPUT_VALIDATION-------------------------------
*/

/*
** input_validation.c
*/
int		input_validation(t_data *data);
int		validate_command_seperators(t_data *data, char *charachter);
int		validate_end_of_line_command(t_data *data, char *charachter, int len);
int		validate_start_of_line_command(t_data *data, char *charachter);

/*
** validate_quote.c
*/
int		validate_single_quotes(t_data *data, char *charachter);
int		validate_double_quotes(t_data *data, char *charachter);

/*
** validate_redirections.c
*/
int		validate_input_redirection(t_data *data, char *charachter);
int		validate_output_redirection(t_data *data, char *charachter);
int		validate_pipes(t_data *data, char *charachter);
int		replace_double_pipes(t_data *data);
void	reduce_input_str(t_data *data, int reduction, int *i);

/*
**--FOLDER------------------8_HANDLE_SIGNALS------------------------------------
*/

/*
** handle_signal.c
*/
void	signal_handler(void);
void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	print_prompt(void);

void	print_array(char **array);

#endif
