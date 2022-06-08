/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:50:44 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/04 10:55:37 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	signed char	in_decrement;
	size_t		last;
	size_t		current;

	if (dst != src)
	{
		if (dst < src)
		{
			in_decrement = 1;
			current = 0;
			last = len;
		}
		else
		{
			in_decrement = -1;
			current = len - 1;
			last = -1;
		}
		while (current != last)
		{
			*((char *)dst + current) = *((char *)src + current);
			current += in_decrement;
		}
	}
	return (dst);
}
