/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:27:59 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/02 19:40:36 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*t;

	t = (unsigned char *)s;
	while (*t != (unsigned char)c && *t)
		t++;
	if (*t == (unsigned char)c)
		return ((char *)t);
	else
		return (0);
}
