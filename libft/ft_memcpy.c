/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:34:14 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/04 17:53:00 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst1;
	char	*src1;
	size_t	i;

	dst1 = (char *)dst;
	src1 = (char *)src;
	if (src1 == 0 && dst1 == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	dst = (void *)dst1;
	return (dst);
}
