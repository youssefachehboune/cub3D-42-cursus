/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:23:13 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/11 15:48:23 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocate(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i] && i < len)
		i++;
	return ((char *)malloc(sizeof(char) * (i + 1)));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		sub = (char *)malloc(sizeof(char));
		*sub = 0;
		return (sub);
	}
	sub = ft_allocate(s, start, len);
	if (sub == 0)
		return (0);
	ft_strlcpy(sub, (s + start), len + 1);
	return (sub);
}
