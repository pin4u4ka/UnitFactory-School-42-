/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmparr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinchuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:19:09 by apinchuk          #+#    #+#             */
/*   Updated: 2017/06/29 16:19:11 by apinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cmparr(const char *s1, char s2[][9], int size)
{
	size_t	i;

	i = 0;
	while (size != (-1))
	{
		while (s1[i] != '\0' && s2[size][i] != '\0' && s1[i] == s2[size][i])
			i++;
		if (ft_strlen(s1) == i)
			return (1);
		i = 0;
		size--;
	}
	return (0);
}
