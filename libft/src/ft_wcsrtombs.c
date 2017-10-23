/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsrtombs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:27:02 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/23 12:27:03 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcsrtombs(char *str, wchar_t *wcs, size_t lenmax)
{
	int		i;
	int		ret;
	size_t	res;
	size_t	size;

	i = 0;
	ret = 0;
	res = 0;
	if (!(size = ft_wcsrlen(wcs, lenmax)))
		return (0);
	if (!str)
		return (size);
	while (res < size)
	{
		ret = ft_wcrtomb(&(str[res]), wcs[i]);
		res += ret;
		i++;
	}
	return (res);
}
