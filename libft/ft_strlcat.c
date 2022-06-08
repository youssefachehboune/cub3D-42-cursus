/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:42:38 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/01 19:55:24 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	else if (dlen >= dstsize)
		return (dstsize + slen);
	while (i < dstsize - dlen - 1 && src[i])
	{
		dst[i + dlen] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
