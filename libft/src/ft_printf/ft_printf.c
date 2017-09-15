/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 15:58:49 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 19:08:16 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
static int	ft_printf_tostr(char **ret, t_list *list)
{
	t_list	*todel;
	char	*tmp;
	int		size;
	int		i;

	todel = list;
	size = 1;
	i = 0;
	while (todel && (size += todel->content_size))
		todel = todel->next;
	*ret = ft_strnew((size_t)size);
	tmp = *ret;
	while (list && *ret)
	{
		todel = list;
		ft_memcpy(tmp, list->content, (list->content_size));
		tmp = ft_strchr(tmp, '\0');
		i += list->content_size;
		ft_memdel(&(list->content));
		list = list->next;
		free(todel);
	}
	return (i);
}

int			ft_asprintf(char **ret, const char *format, ...)
{
	va_list	ap;
	t_list	*list;
	int		i;
	int		nullchar;

	i = 0;
	nullchar = 0;
	va_start(ap, format);
	list = ft_printf_tolst((char*)format, &nullchar, &ap);
	va_end(ap);
	if (list)
		i = ft_printf_tostr(ret, list);
	return (i);
}
*/

static int	print_format(char *format)
{
	int		i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	if (*format != '%')
		ft_putstr_minlen(format, i);
	return (i);
}

int			ft_printf(const char *format, ...)
{
	t_ftplst	*list;
	va_list		ap;
	int			ret;
	int			i;

	ret = 0;
	i = 0;
	list = ft_get_flag(format);
	va_start(ap, format);
	ft_printf_tolst(list, &ap);
	va_end(ap);
	while (*format)
	{
		if (*(format += i) == '%' && list)
		{
			ft_putstr_minlen(list->arg, list->size);
			ret += list->size;
			format += ft_strlen(list->flag);
			ft_ftplstdel(&list);
		}
		else if (*format == '%')
			format++;
		i = print_format((char*)format);
		ret += i;
	}
	return (ret);
}
