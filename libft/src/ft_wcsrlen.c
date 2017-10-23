/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:26:12 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/23 12:26:34 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcsrlen(wchar_t *wcs, size_t lenmax)
{
	int		i;
	int		size;
	size_t	ret;

	i = 0;
	ret = 0;
	while (wcs[i] && ret < lenmax)
	{
		size = ft_wcrtomb(NULL, wcs[i]);
		ret += size;
		if (size > MB_CUR_MAX)
			return (0);
		i++;
	}
	if (ret > lenmax)
		ret -= size;
	return (ret);
}
