/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:14:45 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/03 14:20:29 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	l;

	l = ft_strlen(needle);
	if (!ft_strncmp(needle, "", 1))
		return ((char *)haystack);
	if (!*haystack)
		return (0);
	while (len)
	{
		if (haystack == ft_strchr(haystack, needle[0]))
			if (!ft_strncmp(haystack, needle, l) && len >= l)
				return ((char *)haystack);
		len--;
		haystack++;
	}
	return (0);
}
