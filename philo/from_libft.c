/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:57:20 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/06 14:40:56 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (0);
	while (str[n])
		n++;
	return (n);
}

static int	mk_check_atoi(const char *str, int n, int s)
{
	int				a;
	unsigned long	l;

	a = 0;
	l = 0;
	while (str[n + a] >= '0' && str[n + a] <= '9')
		a++;
	if (str[n + a])
		return (0);
	if (a > 10 && s == 1)
		return (0);
	if (a > 10 && s == -1)
		return (0);
	while (str[n] >= '0' && str[n] <= '9')
	{
		l *= 10;
		l += str[n] - '0';
		n++;
	}
	if (l > 2147483647 && s == 1)
		return (0);
	if (l > 2147483648 && s == -1)
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int	s;
	int	n;
	int	nombre;

	nombre = 0;
	n = 0;
	s = 1;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\n'
		|| str[n] == '\r' || str[n] == '\v' || str[n] == '\f')
		n++;
	if (str[n] == '+' || str[n] == '-')
	{
		if (str[n] == '-')
			s = -s;
		n++;
	}
	if (mk_check_atoi(str, n, s) == 0)
		return (mk_check_atoi(str, n, s));
	while (str[n] >= '0' && str[n] <= '9')
	{
		nombre *= 10;
		nombre += str[n] - '0';
		n++;
	}
	return (nombre * s);
}

void	ft_putnbr(int n)
{
	unsigned int	t;
	char			c;

	if (n < 0)
	{
		t = -n;
		write(1, "-", 1);
	}
	else
		t = n;
	if (t > 9)
		ft_putnbr(t / 10);
	t %= 10;
	c = t + '0';
	write(1, &c, 1);
}
