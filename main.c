/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:34:07 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/02 15:32:14 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_start(char *str, pthread_t **thread, pthread_mutex_t **mutex)
{
	if (thread)
		free(thread);
	if (mutex)
		free(mutex);
	write(2, "philo: ", 7);
	write(2, str, ft_strlen(str));
	exit(1);
}

static char	first_char(char *str)
{
	size_t	n;

	n = 0;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\n'
		|| str[n] == '\r' || str[n] == '\v' || str[n] == '\f')
		n++;
	if (str[n] == '+' || str[n] == '-')
		n++;
	return (str[n]);
}

static int	check(int ac, char **av)
{
	int	n;
	int	ck;

	n = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (n < ac)
	{
		ck = ft_atoi(av[n]);
		if ((ck == 0 && first_char(av[n]) != '0') || ck < 1)
			return (0);
		n++;
	}
	return (1);
}

static void	alloc_init(t_data *data, int ac, char **av)
{
	int	n;

	n = 0;
	if (!check(ac, av))
		error_start(E_ARG, NULL, NULL);
	data->len = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->t_must = -1;
	if (ac == 6)
		data->t_must = ft_atoi(av[5]);
	data->thread = malloc(data->len * sizeof(pthread_t *));
	if (!data->thread)
		error_start(E_ALLOC, NULL, NULL);
	data->mutex = malloc(data->len * sizeof(pthread_mutex_t *));
	if (!data->mutex)
		error_start(E_ALLOC, data->thread, NULL);
	while (n < data->len)
	{
		data->thread[n] = NULL;
		data->mutex[n] = NULL;
		n++;
	}
	data->access = NULL;
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.stop = 0;
	alloc_init(&data, argc, argv);
	data.access = malloc((data.len + 1) * sizeof(t_access));
	if (!data.access)
		error_start(E_ALLOC, data.thread, data.mutex);
	init(&data);
	philo(&data);
	return (0);
}
