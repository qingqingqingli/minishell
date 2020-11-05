/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <rbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 15:51:27 by rbakker       #+#    #+#                 */
/*   Updated: 2020/10/19 11:54:08 by rbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

typedef struct		s_format
{
	int			min_flag;
	int			zero_flag;
	int			width;
	int			precision;
	int			precision_nb;
	char		specifier;
	int			output;
}					t_format;

int					ft_printf(const char *str, ...);

void				ft_putnbr(long long n, t_format *format);
void				write_function(char c, t_format *format);
void				ft_putstr(char *s, int size, t_format *format);
int					ft_strlenn(char *s);
int					integer_len(long long n);
void				write_negative_function(int *sign, t_format *format);
int					specifier_checker(const char *str, int *spot, int count);

void				print_charachters(const char *str, int *spot,
										t_format *format);
void				reset_struct(t_format *format);
void				reset_output(t_format *format);
void				scan_flags(const char *str, int *spot, t_format *format,
								int count);
void				scan_wildcard(const char *str, int *spot, t_format *format,
									va_list arguments);
void				scan_specifier(const char *str, int *spot, t_format *format,
									int count);
void				handeling_negatives(t_format *format);
void				generate_output(t_format *format, va_list arguments);

void				signed_integer_output(t_format *format, va_list arguments,
											int sign);
void				number_zero(t_format *format);
void				min_flag_d_i(t_format *format, int value, int sign);
void				zero_flag_d_i(t_format *format, int value, int sign);
void				no_flag_d_i(t_format *format, int value, int sign);

void				charachter_output(t_format *format, va_list arguments);
void				min_flag_c(t_format *format, va_list arguments);
void				no_flag_c(t_format *format, va_list arguments);

void				string_output(t_format *format, va_list arguments);
void				min_flag_s(t_format *format, va_list arguments);
void				zero_flag_s(t_format *format, va_list arguments);
void				no_flag_s(t_format *format, va_list arguments);

void				pointer_output(t_format *format, va_list arguments);
void				no_flag_p(t_format *format, va_list arguments);
void				min_flag_p(t_format *format, va_list arguments);

void				unsigned_integer_output(t_format *format,
											va_list arguments);
void				min_flag_u(t_format *format, unsigned int value);
void				zero_flag_u(t_format *format, unsigned int value);
void				no_flag_u(t_format *format, unsigned int value);

void				hexa_lower_output(t_format *format, va_list arguments);
int					hex_len(unsigned long value);
void				ft_puthex_lower(unsigned long value, t_format *format);
void				no_flag_x(t_format *format, unsigned int value);
void				zero_flag_x(t_format *format, unsigned int value);
void				min_flag_x(t_format *format, unsigned int value);

void				hexa_upper_output(t_format *format, va_list arguments);
void				ft_puthex_upper(unsigned int value, t_format *format);
void				no_flag_xx(t_format *format, unsigned int value);
void				zero_flag_xx(t_format *format, unsigned int value);
void				min_flag_xx(t_format *format, unsigned int value);

void				percentage_output(t_format *format);
void				min_flag_perc(t_format *format);
void				zero_flag_perc(t_format *format);
void				no_flag_perc(t_format *format);

#endif
