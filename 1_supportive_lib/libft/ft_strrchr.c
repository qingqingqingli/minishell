/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 14:51:22 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:59:15 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*beginpoint;

	i = 0;
	beginpoint = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			beginpoint = (char*)s + i;
		i++;
	}
	if (beginpoint != 0)
		return (beginpoint);
	if (c == '\0')
		return ((char*)s + i);
	return (0);
}
