/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:16:41 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/02 10:13:08 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*d;

	d = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		d[i] = c;
		i++;
	}
	b = (void *)d;
	return (b);
}
