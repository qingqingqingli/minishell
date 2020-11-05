/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbakker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:54:00 by rbakker       #+#    #+#                 */
/*   Updated: 2020/04/17 11:58:38 by roybakker     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	if (dstsize == 0)
		return (src_len);
	if (dstsize > dst_len)
	{
		while (((dst_len + i) < dstsize - 1) && (src[i] != '\0'))
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	if (dstsize < dst_len)
		return (dstsize + src_len);
	return (dst_len + src_len);
}
