/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:48:46 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/06 18:10:24 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s2_len(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s1);
	while (set[++i] && *s1)
	{
		if (*s1 == set[i])
		{
			len--;
			s1++;
			i = -1;
		}
	}
	i = -1;
	while (set[++i] && *s1)
	{
		if (s1[len - 1] == set[i])
		{
			len--;
			i = -1;
		}
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*s2;

	if (!s1)
		return (0);
	len = s2_len(s1, set);
	i = 0;
	while (set[i] && *s1)
	{
		if (*s1 == set[i])
		{
			s1++;
			i = -1;
		}
		i++;
	}
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (0);
	ft_strlcpy(s2, (char *)s1, len + 1);
	return (s2);
}
